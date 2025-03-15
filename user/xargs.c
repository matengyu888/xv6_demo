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
  printf("buf: %s\n", buf);
  char *p = buf;

  int xargc = 0;
  char *xargv[MAXARG];
  for(int i = 1; i < MAXARG; i++)
  {
    xargv[xargc] = argv[i];
    xargc++;
  }
  exit(0);
}

