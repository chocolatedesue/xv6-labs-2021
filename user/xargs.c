#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"


void debug(char *buf[], int n)
{
    for (int i = 0; i < n; ++i)
    {
        printf("debug-mode arg: %s\n", buf[i]);
    }
}



int main(int argc, char *argv[])
{
    
    
    char buf[MAXARG][100];
    char* m[MAXARG];
    char *command = argv[1];
    for (int i = 2; i < argc; ++i)
    {
        strcpy(buf[i-2],argv[i]);
    }
    int idx = argc - 2;

    char opt = ' ';
    int s = 0;
    while (read(0, &opt, 1) == 1)
    {
        // printf("*%c", opt);
        if (opt == ' ' || opt == '\n')
        {
            if (s == 0)
            {
                continue;
            }
            else
            {
                buf[idx++][s]=0;
                s = 0;              
            }
        }
        else
        {
            buf[idx][s++]=opt;

        }
    }

    if (fork() == 0)
    {
        for (int i = 0;i<idx;++i){
            m[i+1] = buf[i];
        }
        m[0]=command;
        m[idx+1]=0;
        exec(command, m);
        exit(0);
    }
    else
    {
        wait((int *)0);
    }
    exit(0);
}



