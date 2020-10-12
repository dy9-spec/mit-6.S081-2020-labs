#include "kernel/types.h"
#include "user/user.h"

void cull(int fd) {
    int pfd[2], num;
    int i;
    top:
    read(fd, &num, sizeof(num));
    printf("prime %d\n", num);

    pipe(pfd);
    if (fork()) {
        close(pfd[0]);
        for (;;) {
            read(fd, &i, sizeof(i));
            if (i % num != 0) {
                write(pfd[1], &i, sizeof(i));
            }
        }
    } else {
        close(fd);
        close(pfd[1]);
        fd = pfd[0];
        goto top;
    }
}

int main() {
    int p[2];
    pipe(p);

    if (fork()) {
        close(p[1]);
        cull(p[0]);
    } else {
        close(p[0]);
        int n;
        for (n = 2; n < 35; n++) {
            write(p[1], &n, sizeof(n));
        }
    }
    return 0;
}