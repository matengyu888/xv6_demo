#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

char*
fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  return buf;
}

int norecursive(char *path)
{
  char temp[DIRSIZ+1];
  memmove(temp,fmtname(path),strlen(fmtname(path)));
  if(temp[0]=='.')
  {
    return 1;
  }
  return 0;
}

void find(char *path,char *target)
{
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if((fd = open(path, 0)) < 0){
    fprintf(2, "ls: cannot open %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){
    fprintf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }
  printf("hellp\n");
  if(strcmp(fmtname(path),target)==0)
  {
    printf("%s\n",path);
  }

  switch(st.type){
  case T_FILE:
    break;

  case T_DIR:
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf("ls: path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if(de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if(stat(buf, &st) < 0){
        printf("ls: cannot stat %s\n", buf);
        continue;
      }
      printf("%s\n", fmtname(buf));
      if(st.type==T_DIR && !norecursive(buf))
      {
        find(buf,target);
      }
    }
    break;
  }
  close(fd);
}

int
main(int argc, char *argv[])
{

  if(argc < 2){
    fprintf(2, "Usage: find path target\n");
    exit(1);
  }
  else if(argc == 2){
    find(".",argv[1]);
    exit(0);
  }
  else if(argc==3)
  {
    find(argv[1],argv[2]);
    exit(0);
  }
  exit(0);

}
