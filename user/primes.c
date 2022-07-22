#include "kernel/types.h"
#include "user/user.h"
#define PRIME_NUM 35

int primes(int fd);

int main()
{
    int p[2];
    pipe(p);
    if (fork() == 0)
    {
        close(p[1]);
        primes(p[0]);
        close(p[0]);
    }
    else
    {
        close(p[0]);
        for (int i = 2; i <= PRIME_NUM; ++i)
        {
            write(p[1], &i, sizeof i);
        }
        close(p[1]);
        int mark;
        wait(&mark);
    }

    exit(0);
}

int primes(int fd)
{

    int res;
    if (read(fd, &res, sizeof res) != 0)
    {
        printf("prime %d\n", res);
        int p[2];
        pipe(p);
        if (fork() == 0)
        {
            close(p[1]);
            primes(p[0]);
            close(p[0]);
        }
        else
        {
            close(p[0]);
            int temp;
            while (read(fd, &temp, sizeof temp) != 0)
            {
                if (temp % res != 0)
                {
                    write(p[1], &temp, sizeof temp);
                }
            }
            // exit(0)
            close(p[1]);
            int mark;
            wait(&mark);
        }
    }
    close (fd);
    exit(0);
}