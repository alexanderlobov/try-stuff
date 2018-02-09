#include <stdio.h>

int main()
{
    const int BUFSIZE = 128;
    char buf[BUFSIZE];
    FILE *f = popen("echo stdout; echo stderr >&2", "r");
    while (fgets(buf, BUFSIZE, f)) {
        printf("Read from popen: %s", buf);
    }
    pclose(f);
    return 0;
}
