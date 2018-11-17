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

#include <stdio.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

#define IFA_STAT(s)     (((struct if_data *)ifa->ifa_data)->ifi_ ## s)

#define PACKAGE_NAME    "ifcounters"
#define PACKAGE_VERSION "0.1"

void show_help()
{
    printf(
            "Usage: ifcounters [-v] [-h] [-b|-p|-e|-m|-q] interface\n" \
            "\n" \
            "Options:\n" \
            "   -b      Input/Output Bytes counter\n" \
            "   -p      Input/Output Unicast Packets counter\n" \
            "   -e      Input/Output Errors counter\n" \
            "   -m      Input/Output Multicast Packets counter\n" \
            "   -q      Input/Output Queue Drops counter\n" \
            "   -v      Display version information\n" \
            "   -h      Display this help message\n"
            );

}

void show_version()
{
    printf("%s %s\n", PACKAGE_NAME, PACKAGE_VERSION);
    printf("Copyright (c) 2018 by Babak Farrokhi <babak@farrokhi.net>\n");
}

int main(int argc, char **argv)
{
    struct ifaddrs *ifap, *ifa;
    char *ifname, *param;
    int flag, c;

    flag = 0;

    if (argc < 2) {
        show_help();
        exit(0);
    }

    while ((c = getopt(argc, argv, "hvb:p:e:m:q:")) != -1) {

        switch (c) {
            case 'h':
                show_help();
                exit(0);
            case 'v':
                show_version();
                exit(0);
            case 'b':
            case 'p':
            case 'e':
            case 'm':
            case 'q':
                flag = c;
                param = strdup(optarg);
                break;
            case '?':
            default:
                show_help();
                printf("\n");
                show_version();
                exit(1);
        }
    }

    argc -= optind;
    argv += optind;

    if (flag == 0) {
        show_help();
        exit(1);
    }

    if (getifaddrs(&ifap) != 0) {
        fprintf(stderr, "error\n");
    }
    else {
        for (ifa = ifap; ifa; ifa= ifa->ifa_next) {
            ifname = ifa->ifa_name;

            if (strcmp(ifa->ifa_name, param) == 0) {
                switch (flag) {
                    case 'b':
                        printf("rbytes.value %lu\nobytes.value %lu\n", IFA_STAT(ibytes), IFA_STAT(obytes));
                        break;
                    case 'p':
                        printf("rpackets.value %lu\nopackets.value %lu\n", IFA_STAT(ipackets), IFA_STAT(opackets));
                        break;
                    case 'e':
                        printf("rerrors.value %lu\noerrors.value %lu\n", IFA_STAT(ierrors), IFA_STAT(oerrors));
                        break;
                    case 'm':
                        printf("rmcasts.value %lu\nomcasts.value %lu\n", IFA_STAT(imcasts), IFA_STAT(omcasts));
                        break;
                    case 'q':
                        printf("rqdrops.value %lu\noqdrops.value %lu\n", IFA_STAT(iqdrops), IFA_STAT(oqdrops));
                        break;
                    default:
                        printf("invalid flag");
                        exit(1);
                }
                exit(0);
            }

            while (ifa->ifa_next != NULL && 
                    (strcmp(ifa->ifa_next->ifa_name, ifname) == 0))  {
                ifa = ifa->ifa_next;
            }
        }
        printf("Unknown interface: %s\n", param);
        exit(1);
    }
}
