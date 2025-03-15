#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/param.h"

//echo "hello" | xargs echo "world"
//echo "1\n2" | xargs echo "line"
int main(int argc, char *argv[])
{
  sleep(10);
  char buf[MAXARG];
  read(0, buf, MAXARG);
  // printf("buf: %s\n", buf);

  int xargc = 0;
  char *xargv[MAXARG];
  for(int i = 1; i < argc; i++)
  {
    xargv[xargc] = argv[i];
    xargc++;
  }
  char *p = buf;
  for(int i=0;i<MAXARG;i++)
  {
    if(buf[i]=='\n')
    {
      int pid=fork();
      if(pid>0)
      {
        p=&buf[i+1];
        wait(0);
      }
      else if(pid==0)
      {
        buf[i]=0;
        xargv[xargc]=p;
        xargc++;
        xargv[xargc]=0;
        xargc++;
        exec(xargv[0],xargv);
        exit(0);
      }

    }
  }

  wait(0);
  exit(0);
}

