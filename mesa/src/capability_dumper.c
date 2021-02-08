// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include "microchip/ethernet/switch/api/misc.h"
#include "microchip/ethernet/switch/api/capability.h"

int main(int argc, char *argv[]) {
    int i, cap;
    void *handle;
    uint32_t (*capability)(mesa_inst_t, int);

    char *error;

    if (argc < 3) {
        printf("Usage: %s <so-file> <capability>...\n", argv[0]);
        exit(1);
    }

    handle = dlopen(argv[1], RTLD_LAZY);
    if (!handle) {
        fputs(dlerror(), stderr);
        exit(1);
    }

    capability = dlsym(handle, "mesa_capability");
    if ((error = dlerror()) != NULL) {
        fputs(error, stderr);
        exit(1);
    }

    for (i = 2; i < argc; ++i) {
        cap = atoi(argv[i]);
        printf("%d %u\n", cap, (*capability)(0, cap));
        fflush(stdout);
    }

    dlclose(handle);

    return 0;

}
