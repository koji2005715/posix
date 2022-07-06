#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FILENAME "/tmp/hoge"

int main()
{
  int fd;
  char buf[1024];
  int len;

  mkfifo(FILENAME, 0666);

  fd = open(FILENAME, O_RDONLY);

  while (1) {
    len = read(fd, buf, sizeof(buf)-1);
    if (len == 0)
      break;
    fputs(buf, stdout);
  }
  close(fd);
}
  
