#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


void runpross(int readfd)
{
    int f_fork;
    int prime;
    int pipes[2];
    int num;
    while(1)
    {
        if(read(readfd, &num, sizeof(num)) == 0)
        {
            close(readfd);
            int child;  
            wait(&child);
            exit(0);
        }
        if(prime==0)
        {
            prime=num;
            printf("Prime: %d\n", prime);
        }

        if(num%prime!=0)
        {
            if(!f_fork)
            {
                pipe(pipes);
                f_fork=1;
                if(fork()==0)
                {
                    close(pipes[1]);
                    runpross(pipes[0]);
                }
                else
                {
                    close(pipes[0]);
                }
            }
            write(pipes[1], &num, sizeof(num));

        }
    }

}

int main(int argc, char *argv[]) {
    int p[2];
    pipe(p);
    for(int i=2;i<36;i++)
    {
        write(p[1], &i, sizeof(i));
    }
    close(p[1]);
    runpross(p[0]);

  }