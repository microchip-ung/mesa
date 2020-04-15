/*
 Copyright (c) 2004-2019 Microsemi Corporation "Microsemi".

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
*/

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include "mscc/ethernet/switch/api/misc.h"
#include "mscc/ethernet/switch/api/capability.h"

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
