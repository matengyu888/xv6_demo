#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


void runpross(int readfd)
{
    int f_fork=0;
    int prime=0;
    int pipes[2];
    int num=0;
    while(1)
    {
        int read_bytes = read(readfd, &num, 4);

        // left neighbor has no more number to provide
        if (read_bytes == 0) {
          close(readfd);
          if (f_fork) {
            // tell my children I have no more number to offer
            close(pipes[1]);
            // wait my child termination
            int child_pid;
            wait(&child_pid);
          }
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
                    close(readfd);
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
    exit(0);
  }