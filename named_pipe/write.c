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

  mkfifo(FILENAME, 0666);

  fd = open(FILENAME, O_WRONLY);

  while (1) {
    fgets(buf, sizeof(buf)-1, stdin);
    if (feof(stdin))
      break;
    write(fd, buf, strlen(buf));
  }
  close(fd);
}
  
