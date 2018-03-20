#include <unistd.h>
#include <stdio.h>
#include <poll.h>
#include <string.h>

enum {
    PIPE_READ = 0,
    PIPE_WRITE = 1,
};

void child(int fd)
{
    const char *s = "hello";
    write(fd, s, strlen(s));
    close(fd);
    // pause();
}

void parent(int fd)
{
    struct pollfd fds[] = {{fd, POLLIN, 0}}; 
    const size_t fds_size = sizeof(fds)/sizeof(struct pollfd);
    printf("fds_size=%ld\n", fds_size);

    const size_t BUFSIZE = 4096;
    char buf[BUFSIZE];
    long timeout = 1000;

    while (1) {
        int poll_result = poll(fds, fds_size, timeout);
        printf("poll_result is %d\n", poll_result);

        if (fds[0].revents & POLLIN) {
            printf("input of fd %d: ", fds[0].fd);
            const int n = read(fd, buf, BUFSIZE - 1);
            if (n > 0) {
                buf[n] = '\0';
                printf("'%s'\n", buf);
            } else if (0 == n) {
                puts("EOF");
                return;
            }
        }
        if (fds[0].revents & POLLHUP) {
            printf("POLLHUP on fd %d\n", fd);
        }
    }
}

int main()
{
    // create a pipe
    // spawn a child
    // 1. exit from child. Is there EOF of error condition on the pipe?
    // 2. kill the child. The same questions.
    // 3. try with zmqpp and system pollers.

    int fd[2];
    pipe(fd);

    pid_t child_pid = fork();

    if (child_pid > 0) {
        close(fd[PIPE_WRITE]);
        parent(fd[PIPE_READ]);
    } else if (child_pid == 0) {
        close(fd[PIPE_READ]);
        child(fd[PIPE_WRITE]);
    } else {
        perror("fork");
    }
    return 0;
}
