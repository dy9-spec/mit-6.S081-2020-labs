#include "kernel/types.h"
#include "user/user.h"
int main(int argc, char* argv[]) {

    if (argc < 2) {
        fprintf(2, "Usage: xargs expects the args afterwards");
        exit(1);
    }

    char c;
    int n;
    int i = 0;
    char buf[512];

    while ((n = read(0, &c, 1)) > 0) {

        if (n == 1 && c != '\n') {
            buf[i++] = c;
            continue;
        }

        if (c == '\n') {
            buf[i] = '\0';
            i = 0;


            argv[argc] = buf;

            /**
            int idx;
            for (idx = 1; idx < argc + 1; idx++) {
                printf("before idx: %d, arg: %s\n", idx, argv[idx]);
            }
            **/

            argv[argc + 1] = ((void *) 0);

            /**
            for (idx = 1; idx < argc + 1; idx++) {
                printf("after idx: %d, arg: %s\n", idx, argv[idx]);
            }
            **/



            if (fork()) {
                int child_status;
                wait(&child_status);
            } else {

                exec(argv[1], argv + 1);
                exit(1);
            }
            buf[i] = 0;
        }
    }

    exit(0);
}
