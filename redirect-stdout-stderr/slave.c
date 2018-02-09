#include <stdio.h>

int main()
{
    fputs("slave: stdout\n", stdout);
    fputs("slave: stderr\n", stderr);
    return 0;
}
