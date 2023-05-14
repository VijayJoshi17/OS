#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

#define SYS_ADD 333

int main()
{
    int a = 2, b = 3;
    long result = syscall(SYS_ADD, a, b);
    printf("%d + %d = %ld\n", a, b, result);
    return 0;
}

