#include <iostream>
#include <signal.h>

int fib(int x) {
    if (x == 0) return 0;
    if (x == 1) return 1;
    /* if you want to be able to attach to your program at a specific spot,
     * raising SIGSTOP (`raise(3)` is defined in signal.h) will make the
     * program block until you attach and * continue */
#ifdef STOP_DEMO
    if (x == 5) raise(SIGSTOP);
#endif
    return (fib(x-2) + fib(x-1));
}

int main(int argc, char **argv)
{
    std::cout << fib(atoi(argv[1])) << std::endl;

}
