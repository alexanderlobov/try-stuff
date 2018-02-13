#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <iostream>

extern char **environ;

void wait_print()
{
    pid_t child_pid = wait(nullptr);
    std::cout << "Child with pid " << child_pid << " exited\n\n";
}

int main()
{
    if (0 == fork()) {
        execl("./slave", "slave-xxx", "execl", nullptr);
    }
    wait_print();

    if (0 == fork()) {
        const char * const envp[] = {"TEST=huest", nullptr};
        int res = execle("./slave", "slave", "execle", nullptr, envp);
        std::cout << "execle failed, errno=" << errno << ", "
                  << strerror(errno) << '\n';
        return EXIT_FAILURE;
    }
    wait_print();

    if (0 == fork()) {
        char * const argv[] = {
            "slave", "execve without env", NULL
        };
        char * const envp[] = { NULL };

        execve("./slave", argv, envp);
    }
    wait_print();

    if (0 == fork()) {
        char * const argv[] = {
            "slave", "execve with default environ", NULL
        };

        execve("./slave", argv, environ);
    }
    wait_print();

    std::cout << "Exiting from master\n";
    return 0;
}
