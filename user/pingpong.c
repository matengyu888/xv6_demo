#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int pipe1[2];
    int pipe2[2];
    char buf[1]='a';
    pipe(pipe1);
    pipe(pipe2);
    int ret,pid;
    ret=fork();
    if (ret<0)
    {
        fprintf(2,"fork error\n");
        exit(1);
    }

    else if (ret== 0) {
        pid=getpid();
        close(pipe1[1]);
        close(pipe2[0]);
        read(pipe1[0],buf,1);
        fprintf(1,"%d: received ping\n",pid);
        write(pipe2[1],buf,1);
        exit(0);
        
    } else {

        pid=getpid();
        close(pipe1[0]);
        close(pipe2[1]);
        write(pipe1[1],buf,1);
        read(pipe2[0],buf,1);
        fprintf(1,"%d: received pong\n",pid);
        exit(0);
    }
}
