#include <stdlib.h>
#include <stdio.h>

void log_env_var(const char *name)
{
    printf("%s=%s\n", name, getenv(name));
}

int main()
{
    puts("Hello");
    log_env_var("TEST");
    return 0;
}
