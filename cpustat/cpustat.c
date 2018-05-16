/*-
 * Copyright (c) 2018, Babak Farrokhi
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <devstat.h>
#include <err.h>
#include <kvm.h>
#include <math.h>
#include <stdio.h>
#include <strings.h>
#include <sys/sysctl.h>
#include <sys/types.h>

static struct statinfo cur;
kvm_t *kd = NULL;

static int readvar(kvm_t *kd, const char *name, int nlid, void *ptr,
                   size_t len) {
    size_t nlen = len;

    if (sysctlbyname(name, ptr, &nlen, NULL, 0) == -1) {
        warn("sysctl(%s...) failed", name);
        return (1);
    }
    if (nlen != len) {
        warnx("sysctl(%s...): expected %lu, got %lu", name, (unsigned long)len,
              (unsigned long)nlen);
        return (1);
    }
    return (0);
}

static void cpustats(void) {
    int state;
    double cptime = 0.0;
    char *names[] = {"user", "nice", "system", "interrupt", "idle"};

    readvar(kd, "kern.cp_time", 0, &cur.cp_time, sizeof(cur.cp_time));

    for (state = 0; state < CPUSTATES; ++state)
        cptime += cur.cp_time[state];
    for (state = 0; state < CPUSTATES; ++state)
        printf("%s.value %.0f\n", names[state],
               rint(100. * cur.cp_time[state] / (cptime ? cptime : 1)));
}

int main(void) 
{ 
    cpustats(); 
}
