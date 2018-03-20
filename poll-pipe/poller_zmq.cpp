#include <zmqpp/zmqpp.hpp>
#include <unistd.h>
#include <stdio.h>

enum {
    PIPE_READ = 0,
    PIPE_WRITE = 1,
};

void child(int fd)
{
    const char *s = "hello";
    write(fd, s, strlen(s));
    // pause();
    // close(fd);
}

void parent(int fd)
{
    zmqpp::poller p;

    p.add(fd);

    const size_t BUFSIZE = 4096;
    char buf[BUFSIZE];
    long timeout = 1000;

    while (true) {
        bool should_return = false;
        bool result = p.poll(timeout);
        printf("poll result is %d\n", result);
        if (p.has_input(fd)) {
            printf("input on fd %d: ", fd);
            int n = read(fd, buf, BUFSIZE-1);
            if (n > 0) {
                buf[n] = '\0';
                printf("'%s'\n", buf);
            } else if (0 == n) {
                puts("EOF");
                should_return = true;
            }
        }
        if (p.has_error(fd)) {
            printf("error on fd %d\n", fd);
            should_return = true;
        }

        if (should_return)
            return;
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
}
