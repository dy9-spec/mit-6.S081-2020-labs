#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char** argv) {
    char data_sent_from_parent = 'p';
    char data_sent_from_child = 'c';
    char buf_parent[1];
    char buf_child[1];
    int fd_ping[2];
    int fd_pong[2];

    pipe(fd_ping); // pipe: parent -> child
    pipe(fd_pong); // pipe: child -> parent

    if (fork() == 0) {
        close(fd_ping[1]); // use pipe ping to read in child
        close(fd_pong[0]); // use pipe pong to write in child

        int child_pid = getpid();
        read(fd_ping[0], buf_child, sizeof(buf_child));
        printf("%d: received ping\n", child_pid);
        printf("process %d receives data: %c\n", child_pid, buf_child[0]);

        write(fd_pong[1], &data_sent_from_child, sizeof(data_sent_from_child));

    } else {
        close(fd_ping[0]); // use pipe ping to write in parent
        close(fd_pong[1]); // use pipe pong to read in parent

        write(fd_ping[1], &data_sent_from_parent, sizeof(data_sent_from_parent));

        int parent_pid = getpid();
        read(fd_pong[0], buf_parent, sizeof(buf_parent));
        printf("%d: received pong\n", parent_pid);
        printf("process %d receives data: %c\n", parent_pid, buf_parent[0]);
    }

    exit(0);
}
