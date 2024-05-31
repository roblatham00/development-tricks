#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

void fast(int fd)
{
    int ret, total=0, nbytes=50000;
    char *buf = calloc(nbytes, 1);
    while (total < nbytes) {
        ret = write(fd, buf, nbytes-total);
        total += ret;
    }
    free(buf);
}

void medium(int fd)
{
    int ret, total=0, nbytes=100000;
    char *buf = calloc(nbytes, 1);
    while (total < nbytes) {
        ret = write(fd, buf, nbytes-total);
        total += ret;
    }
    free(buf);
}

void slow(int fd)
{
    int ret, total=0, nbytes=200000;
    char *buf = calloc(nbytes, 1);
    while (total < nbytes) {
        ret = write(fd, buf, nbytes-total);
        total += ret;
    }
    free(buf);
}
int main(int argc, char **argv)
{
    int fd = open("/dev/null", O_WRONLY);
    if (fd == -1) {
        perror("open:");
        return -1;
    }

    for (int i=0; i<1000000; i++) {
        fast(fd);
        medium(fd);
        slow(fd);
    }
    close(fd);
    return 0;
}
