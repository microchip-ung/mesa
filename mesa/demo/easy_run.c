// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define _GNU_SOURCE
#include <sys/signalfd.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/wait.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <time.h>

FILE *log_file;

pid_t pid = -1;
int wstatus = 0;
int poll_timeout = 0;
int child_running = 1;
int pipe_stdin[2] = {-1, -1};
int pipe_stdout[2] = {-1, -1};
int pipe_stderr[2] = {-1, -1};
int stdin_pipe = 1;
int run_in_background = 0;

int lockfile = 0;
#define LOCKFILE_PATH_SIZE 1024
char lockfile_path[LOCKFILE_PATH_SIZE];
struct timespec start_time;

#define PREFIX_SIZE     40
#define POSTFIX_SIZE    10
#define LINE_SIZE_MAX 100000
#define BUF_SIZE      (204800)

#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

struct fddata {
    int fd;

    int source_is_closed;

    struct timespec last_read_time;

    char buf[BUF_SIZE];
    char *data_begin, *data_end, *buf_begin, *buf_end;
};

struct str {
    char *buf;
    size_t buf_valid;
    size_t buf_size;
    size_t buf_free;
    size_t buf_alloc_step;
};

void fddata_init(struct fddata *fdd, int fd) {
    memset(fdd, 0, sizeof(*fdd));
    fdd->fd = fd;
    fdd->data_begin = &fdd->buf[0];
    fdd->data_end = &fdd->buf[0];
    fdd->buf_begin = &fdd->buf[0];
    fdd->buf_end = &fdd->buf[BUF_SIZE];
}

int str_init(struct str *s, size_t alloc_size) {
    memset(s, 0, sizeof(*s));
    s->buf_alloc_step = alloc_size;
    s->buf = malloc(s->buf_alloc_step);

    if (!s->buf)
        return -1;

    s->buf_size = s->buf_alloc_step;
    s->buf_free = s->buf_alloc_step;

    return 0;
}

void str_uninit(struct str *s) {
    if (s->buf)
        free(s->buf);

    memset(s, 0, sizeof(*s));
}

int str_pr_append(struct str *s, const char *fmt, ...) {
    va_list ap;
    int res;

    while (1) {
        va_start(ap, fmt);
        res = vsnprintf(s->buf + s->buf_valid, s->buf_free, fmt, ap);
        va_end(ap);

        if (res >= s->buf_free) {
            char *new_buf = realloc(s->buf, s->buf_size + s->buf_alloc_step);
            if (!new_buf)
                return -1;
            s->buf = new_buf;
            s->buf_size += s->buf_alloc_step;
            s->buf_free += s->buf_alloc_step;
        } else {
            s->buf_valid += res;
            return 0;
        }
    }

    return -1;
}

int str_write(int fd, struct str *s) {
    int res;
    int wr_cnt = 0;

    while (wr_cnt < s->buf_valid) {
        res = write(fd, s->buf, s->buf_valid - wr_cnt);
        if (res <= 0)
            return -1;

        wr_cnt += res;
    }

    return 0;
}

void timespec_diff(struct timespec *a, struct timespec *b, struct timespec *r) {
    if ((b->tv_nsec - a->tv_nsec) < 0) {
        r->tv_sec = b->tv_sec - a->tv_sec - 1;
        r->tv_nsec = b->tv_nsec - a->tv_nsec + 1000000000;
    } else {
        r->tv_sec = b->tv_sec - a->tv_sec;
        r->tv_nsec = b->tv_nsec - a->tv_nsec;
    }

    return;
}

const char *ts(char *buf, int size) {
    struct timespec now;
    struct timespec rel;
    int us, s, res;

    res = clock_gettime(CLOCK_MONOTONIC, &now);
    if (res < 0) {
        snprintf(buf, size, "error");
        return buf;
    }

    timespec_diff(&start_time, &now, &rel);

    s  = rel.tv_sec;
    if (rel.tv_nsec >= 999999500) {
        s++;
        us = 0;
    } else {
        us = rel.tv_nsec / 1000;
    }

    snprintf(buf, size, "%07d.%06d", s, us);
    buf[size - 1] = 0;

    return buf;
}

int flock_fd = -1;
void flock_enter() {
    if (flock_fd == -1)
        return;

    flock(flock_fd, LOCK_EX);
}

void flock_exit() {
    if (flock_fd == -1)
        return;

    flock(flock_fd, LOCK_UN);
}

void pr(const char *msg, const char *fmt, ...) {
    int i;
    va_list ap;
    char ts_buf[32];

    flock_enter();

    printf("ER-M-%05d-%s-%s", pid, ts(ts_buf, 32), msg);

    for (i = strlen(msg); i < 7; ++i)
        printf(" ");


    va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);
    printf("\n");

    flock_exit();
}


int report_error(const char *c) {
    return -1;
}

int report_perror(const char *c) {
    return -1;
}

int child(int argc, char *const argv[], char *const envp[]) {
    int i;
    sigset_t mask;

    for (i = 0; i < 32; ++i)
        signal(i, SIG_DFL);

    sigfillset(&mask);
    sigprocmask(SIG_UNBLOCK, &mask, NULL);

    close(pipe_stdin[1]);
    close(pipe_stdout[0]);
    close(pipe_stderr[0]);

    (void)dup2(pipe_stdin[0], STDIN_FILENO);
    (void)dup2(pipe_stdout[1], STDOUT_FILENO);
    (void)dup2(pipe_stderr[1], STDERR_FILENO);

    return execvpe(argv[0], argv, envp);
}

int select_fd(int *nfds, fd_set *fds, struct fddata *fdd) {
    // File descriptor has been closed
    if (fdd->fd == -1)
        return 0;

    FD_SET(fdd->fd, fds);

    if (fdd->fd > *nfds)
        *nfds = fdd->fd;

    return 1;
}

int select_fd_rd(int *nfds, fd_set *fds, struct fddata *fdd,
                 struct fddata *fdd_extra) {
    // If it is a read, then we need to have some buffer space
    if (fdd->data_end == fdd->buf_end)
        return 0;

    // If we have an extra buffer, then both needs to have some room
    if (fdd_extra && fdd_extra->data_end == fdd_extra->buf_end)
        return 0;

    return select_fd(nfds, fds, fdd);
}

int select_fd_wr(int *nfds, fd_set *fds, struct fddata *fdd) {
    // If it is a write, then we need some data to write
    if (fdd->data_begin == fdd->data_end)
        return 0;

    return select_fd(nfds, fds, fdd);
}

int select_fd_sig(int *nfds, fd_set *fds, int fd) {
    if (!child_running)
        return 0;

    FD_SET(fd, fds);

    if (fd > *nfds)
        *nfds = fd;

    return 1;
}

void check_fdd(struct fddata *fdd) {
    if (!fdd)
        return;

    assert(fdd->data_begin <= fdd->data_end);
    assert(fdd->buf_begin <= fdd->buf_end);
    assert(fdd->data_begin <= fdd->buf_end);
    assert(fdd->data_begin >= fdd->buf_begin);
    assert(fdd->data_end <= fdd->buf_end);
    assert(fdd->data_end >= fdd->buf_begin);
}

void fddata_move_to_front(struct fddata *fdd) {
    check_fdd(fdd);

    if (fdd->data_begin == fdd->data_end) {
        fdd->data_begin = fdd->buf_begin;
        fdd->data_end = fdd->buf_begin;
    } else {
        int diff = fdd->data_end - fdd->data_begin;
        memmove(fdd->buf_begin, fdd->data_begin, diff);
        fdd->data_begin = fdd->buf_begin;
        fdd->data_end = fdd->buf_begin + diff;
    }
}

const char *find(const char *b, const char *e, char c) {
    while (b != e) {
        if (*b == c)
            break;
        else
            b++;
    }

    return b;
}

void copy_to_buffer(fd_set *fds, struct fddata *fdd, struct fddata *fdd_extra) {
    size_t buf_free;
    ssize_t s;

    if (fdd->fd == -1)
        return;

    if (!FD_ISSET(fdd->fd, fds))
        return;

    buf_free = fdd->buf_end - fdd->data_end;
    if (fdd_extra)
        buf_free = MIN(buf_free, fdd_extra->buf_end - fdd_extra->data_end);

    s = read(fdd->fd, fdd->data_end, buf_free);
    clock_gettime(CLOCK_MONOTONIC, &fdd->last_read_time);

    if (s == 0) {
        close(fdd->fd);
        fdd->fd = -1;

    } else if (s < 0) {
        // todo error handling
        close(fdd->fd);
        fdd->fd = -1;

    } else {
        if (fdd_extra) {
            memcpy(fdd_extra->data_end, fdd->data_end, s);
            fdd_extra->data_end += s;
        }

        fdd->data_end += s;
    }
}

int line_is_too_long(struct fddata *from, struct fddata *to) {
    const char *lb;
    int rx_size;

    lb = find(from->data_begin, from->data_end, '\n');

    // size of line, or size of buffer
    rx_size = lb - from->data_begin;

    return rx_size >= LINE_SIZE_MAX;
}

int line_timeout(struct fddata *from) {
    struct timespec now;
    struct timespec diff;
    clock_gettime(CLOCK_MONOTONIC, &now);

    timespec_diff(&from->last_read_time, &now, &diff);

    return diff.tv_sec >= 1;
}

void copy_buf_to_buf(struct fddata *from, struct fddata *to,
                     const char *prefix_msg) {
    const char *lb;
    int i, copy_size, to_free_size, from_valid_size, tx_full;
    int prefix_size, postfix_size, line_size, tx_size;
    char prefix_buf[PREFIX_SIZE];
    char postfix_buf[POSTFIX_SIZE];
    char prefix_msg_buf[7];
    char ts_buf[32];

    check_fdd(from);
    check_fdd(to);

    if (from->fd == -1)
        to->source_is_closed = 1;

    to_free_size = to->buf_end - to->data_end;
    from_valid_size = from->data_end - from->data_begin;
    copy_size = MIN(to_free_size, from_valid_size);

    if (!prefix_msg) {
        for (i = 0; i < copy_size; ++i)
            *to->data_end++ = *from->data_begin++;
        fddata_move_to_front(from);
        return;
    }

    postfix_size = snprintf(postfix_buf, POSTFIX_SIZE, "\n");
    strncpy(prefix_msg_buf, prefix_msg, 7);
    prefix_msg_buf[6] = 0;

    tx_full = 0;
    while (from->data_begin != from->data_end && !tx_full) {
        int copy_to_tx = 0;
        lb = find(from->data_begin, from->data_end, '\n');
        line_size = lb - from->data_begin;

        // Check and see if we have a complete line in the input buffer
        if (lb != from->data_end) {
            prefix_size = snprintf(prefix_buf, PREFIX_SIZE, "ER-L-%05d-%s-%s ",
                                   pid, ts(ts_buf, 32), prefix_msg_buf);
            copy_to_tx = 1;

        } else if (line_is_too_long(from, to)) {
            prefix_size = snprintf(prefix_buf, PREFIX_SIZE, "ER-C-%05d-%s-%s ",
                                   pid, ts(ts_buf, 32), prefix_msg_buf);
            line_size = MIN(line_size, LINE_SIZE_MAX);
            copy_to_tx = 1;

        } else if (line_timeout(from)) {
            prefix_size = snprintf(prefix_buf, PREFIX_SIZE, "ER-T-%05d-%s-%s ",
                                   pid, ts(ts_buf, 32), prefix_msg_buf);
            copy_to_tx = 1;

        }

        if (!copy_to_tx) {
            poll_timeout = 1;
            break;
        }

        tx_size = line_size + prefix_size + postfix_size;

        // Check and see if we have room for this in the output buffer
        if (tx_size <= to->buf_end - to->data_end) {
            memcpy(to->data_end, prefix_buf, prefix_size);
            to->data_end += prefix_size;

            memcpy(to->data_end, from->data_begin, line_size);
            from->data_begin += line_size;
            to->data_end += line_size;

            memcpy(to->data_end, postfix_buf, postfix_size);
            to->data_end += postfix_size;

            if (from->data_begin != from->data_end && *from->data_begin == '\n')
                from->data_begin++;

        } else {
            tx_full = 1;
        }
    }

    fddata_move_to_front(from);

#undef PREFIX_BUF_SIZE
}

void copy_to_fd(fd_set *fds, struct fddata *fdd) {
    ssize_t s;

    if (fdd->fd == -1)
        return;

    // if no data or output descriptor is not ready
    if (fdd->data_begin == fdd->data_end || !FD_ISSET(fdd->fd, fds))
        return;

    s = write(fdd->fd, fdd->data_begin, fdd->data_end - fdd->data_begin);

    if (s <= 0) {
        close(fdd->fd);
        fdd->fd = -1;

    } else {
        fdd->data_begin += s;
    }

    fddata_move_to_front(fdd);
}

void copy_to_term(fd_set *fds, struct fddata *fdd) {
    ssize_t s;

    if (fdd->fd == -1) {
        return;
    }

    // if no data or output descriptor is not ready
    if (fdd->data_begin == fdd->data_end || !FD_ISSET(fdd->fd, fds)) {
        return;
    }

    flock_enter();

    while (fdd->data_begin != fdd->data_end) {
        s = write(fdd->fd, fdd->data_begin, fdd->data_end - fdd->data_begin);

        if (s <= 0) {
            close(fdd->fd);
            fdd->fd = -1;
            break;
        } else {
            fdd->data_begin += s;
        }
    }

    flock_exit();

    fddata_move_to_front(fdd);
}

void handle_sigchld() {
    while (1) {
        pid_t p = waitpid(pid, &wstatus, WNOHANG);
        if (p == -1 || p == 0) {
            return;
        } else if (p == pid) {
            child_running = 0;
        }
    }
}

void handle_signals(int fd) {
    int s;
    struct signalfd_siginfo fdsi;

    while (1) {
        s = read(fd, &fdsi, sizeof(struct signalfd_siginfo));

        if (s != sizeof(struct signalfd_siginfo))
            return;

        if (fdsi.ssi_signo == SIGCHLD) {
            handle_sigchld();

        } else {
            kill(pid, fdsi.ssi_signo);
        }
    }
}

int usage(int res) {
    printf("Usage: er [-l lock-file] [-sh] -- <program and options>\n");
    printf("\n");
    printf("Where:\n");
    printf("  -b               Run in background\n");
    printf("  -h               This help message\n");
    printf("  -l <lock-file>   Is the path the a lock file for IO sync\n");
    printf("  -s               Flag to skip the stdin pipe\n");

    return res;
}

int main(int argc, char *const argv[], char *const envp[]) {
    fd_set rd_fds, wr_fds;
    struct fddata rd_in, rd_in_echo, rd_out, rd_err;
    struct fddata wr_in, wr_out;
    int i, cnt, res = 0, nfds = 0, sigfd, child_arg_split = -1, opt;
    const char *msg;
    sigset_t mask;
    int msg_no;

    int child_argc;
    int parent_argc;

    if (argc < 2) {
        return usage(-1);
    }

    for (i = 0; i < argc; ++i) {
        if (strcmp("--", argv[i]) == 0) {
            child_arg_split = i;
            break;
        }
    }

    if (child_arg_split == -1 || child_arg_split + 1 >= argc) {
        return usage(-1);
        return -1;
    } else {
        child_argc = argc - child_arg_split - 1;
        parent_argc = child_arg_split;
    }

    while ((opt = getopt(parent_argc, argv, "bl:sh")) != -1) {
        switch (opt) {
            case 'b':
                run_in_background = 1;
                stdin_pipe = 0;
                break;

            case 'l':
                strncpy(lockfile_path, optarg, LOCKFILE_PATH_SIZE);
                lockfile_path[LOCKFILE_PATH_SIZE - 1] = 0;
                lockfile = 1;
                break;

            case 's':
                stdin_pipe = 0;
                break;

            case 'h':
                return usage(0);

            default: /* '?' */
                return usage(-1);
        }
    }

    if (run_in_background)
        if (daemon(1, 1) < 0)
            return report_perror("Daemon failed");

    //sigemptyset(&mask);
    //sigaddset(&mask, SIGCHLD);

    sigfillset(&mask);
    sigprocmask(SIG_BLOCK, &mask, NULL);
    sigfd = signalfd(-1, &mask, SFD_NONBLOCK);

    if (pipe(pipe_stdin) < 0)
       return report_perror("Pipe stdin failed");
    if (pipe(pipe_stdout) < 0)
       return report_perror("Pipe stdout failed");
    if (pipe(pipe_stderr) < 0)
       return report_perror("Pipe stderr failed");

    clock_gettime(CLOCK_MONOTONIC, &start_time);
    pid = fork();
    if (pid == -1)
        return report_perror("Fork failed");

    if (pid == 0)
        return child(child_argc, argv + child_arg_split + 1, envp);

    if (lockfile)
        flock_fd = open(lockfile_path, O_CREAT | O_RDWR | O_CLOEXEC, 0666);

    {
        struct str s;
        char ts_buf[32];
        str_init(&s, 1024);

        str_pr_append(&s, "ER-M-%05d-%s-RUN    %s", pid, ts(ts_buf, 32),
                      argv[child_arg_split + 1]);

        for (i = 2; i <= child_argc; ++i) {
            str_pr_append(&s, " %s", argv[child_arg_split + i]);
        }

        str_pr_append(&s, "\n");

        flock_enter();
        str_write(STDOUT_FILENO, &s);
        flock_exit();

        str_uninit(&s);
    }

    close(pipe_stdin[0]);
    close(pipe_stdout[1]);
    close(pipe_stderr[1]);

    fddata_init(&rd_in, STDIN_FILENO);
    fddata_init(&rd_in_echo, -1);
    fddata_init(&wr_in, pipe_stdin[1]);
    fddata_init(&rd_out, pipe_stdout[0]);
    fddata_init(&wr_out, STDOUT_FILENO);
    fddata_init(&rd_err, pipe_stderr[0]);
    close(STDERR_FILENO);

    if (!stdin_pipe) {
        close(STDIN_FILENO);
        close(pipe_stdin[1]);
        rd_in.fd = -1;
        wr_in.fd = -1;
    }

    while (1) {
        nfds = 0;
        FD_ZERO(&rd_fds);
        FD_ZERO(&wr_fds);

        cnt = 0;
        cnt += select_fd_rd(&nfds, &rd_fds, &rd_in, &rd_in_echo);
        cnt += select_fd_wr(&nfds, &wr_fds, &wr_in);
        cnt += select_fd_wr(&nfds, &wr_fds, &wr_out);
        cnt += select_fd_sig(&nfds, &rd_fds, sigfd);

        // We only want to read more outout from the process if the terminal
        // output buffer is empty
        if (wr_out.data_begin == wr_out.data_end) {
            cnt += select_fd_rd(&nfds, &rd_fds, &rd_out, 0);
            cnt += select_fd_rd(&nfds, &rd_fds, &rd_err, 0);
        }

        if (cnt == 0)
            break;

        if (poll_timeout) {
            struct timeval t = {};
            t.tv_usec = 100000;  // 100ms
            res = select(nfds + 1, &rd_fds, &wr_fds, 0, &t);
            poll_timeout = 0;

        } else {
            res = select(nfds + 1, &rd_fds, &wr_fds, 0, 0);
        }

        if (res == -1)
            break;

        if (FD_ISSET(sigfd, &rd_fds))
            handle_signals(sigfd);

        if (!child_running) {
            if (rd_in.fd != -1) {
                close(rd_in.fd);
                rd_in.fd = -1;
            }

            if (wr_in.fd != -1) {
                close(wr_in.fd);
                wr_in.fd = -1;
            }
        }

        copy_to_buffer(&rd_fds, &rd_in,  &rd_in_echo);
        copy_to_buffer(&rd_fds, &rd_out, 0);
        copy_to_buffer(&rd_fds, &rd_err, 0);

        copy_buf_to_buf(&rd_in,      &wr_in,  0);
        copy_buf_to_buf(&rd_in_echo, &wr_out, "STDIN ");
        copy_buf_to_buf(&rd_out,     &wr_out, "STDOUT");
        copy_buf_to_buf(&rd_err,     &wr_out, "STDERR");

        copy_to_fd(&wr_fds, &wr_in);
        copy_to_term(&wr_fds, &wr_out);

        // Need to re-fill the potential emptied buffers such that the write
        // file descriptors will go into the select call.
        copy_buf_to_buf(&rd_in,      &wr_in,  0);
        copy_buf_to_buf(&rd_in_echo, &wr_out, "STDIN ");
        copy_buf_to_buf(&rd_out,     &wr_out, "STDOUT");
        copy_buf_to_buf(&rd_err,     &wr_out, "STDERR");


        if (rd_in.fd == -1 && wr_in.data_begin == wr_in.data_end) {
            if (wr_in.fd != -1) {
                close(wr_in.fd);
                wr_in.fd = -1;
            }
        }
    }

    if (child_running)
        waitpid(pid, &wstatus, 0);

    if (WIFEXITED(wstatus)) {
        msg = "EXIT";
        msg_no = WEXITSTATUS(wstatus);

    } else if (WIFSIGNALED(wstatus)) {
        msg = "SIGNAL";
        msg_no = WTERMSIG(wstatus);

    } else {
        msg = "TERM?";
        msg_no = -1;

    }

    pr(msg, "%d", msg_no);
    if (flock_fd != -1) {
        close(flock_fd);
        flock_fd = -1;
    }

    return 0;
}
