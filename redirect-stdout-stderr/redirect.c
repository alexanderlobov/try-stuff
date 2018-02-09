#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>

int main()
{
    puts("master: hello");

    int pipefd[2];
    pipe(pipefd);

    const int pipe_read = pipefd[0];
    const int pipe_write = pipefd[1];

    if (fork() == 0) {
        close(pipe_read);
        dup2(pipe_write, STDOUT_FILENO);
        dup2(pipe_write, STDERR_FILENO);
        close(pipe_write);

        execl("./slave", "slave", NULL);
    } else {
        close(pipe_write);

        const int BUFSIZE = 128;
        char buf[BUFSIZE];

        int res = 0;
        while ( (res = read(pipe_read, buf, BUFSIZE-1)) > 0) {
            buf[res] = '\0';
            printf("master: read from the pipe '%s'\n", buf);
        }

        puts("master: waiting for the slave");
        while (1) {
            pid_t child_pid = wait(NULL);
            if (child_pid != -1)
                printf("child with pid %d was waited\n", child_pid);
            else if (errno != EINTR)
                break;
        }
    }
    return 0;
}
