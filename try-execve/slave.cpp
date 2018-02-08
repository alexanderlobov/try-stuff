#include <iostream>
#include <stdlib.h>
#include <unistd.h>

void print_env_var(const char* name)
{
    const char *value = getenv(name);
    std::cout << name << "=";
    if (value) {
        std::cout << getenv(name);
    } else {
        std::cout << "undefined";
    }
    std::cout << '\n';
}

int main(int argc, char *argv[])
{
    if (argc > 1) {
        std::cout << "Hello from slave " << argv[1] << '\n';
    } else {
        std::cout << "Usage: slave <description>\n";
        return EXIT_FAILURE;
    }
    print_env_var("PATH");
    print_env_var("TEST");
    sleep(10);
    return 0;
}
