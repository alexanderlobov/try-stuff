#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    setenv("TEST", "testvalue", 0);
    if (fork() == 0) {
        execl("./check-env", "check-env", NULL);
    } else {
        pid_t pid = wait(0);
        printf("Child %d is waited\n", pid);
    }
    return 0;
}
