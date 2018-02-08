#include <zmq.h>

int main()
{
    int major, minor, patch;
    zmq_version(&major, &minor, &patch);
    printf("zmq version: %d.%d.%d\n", major, minor, patch);
    return 0;
}
