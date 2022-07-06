#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
  int fd;
  const char* msg = "message\n";

  fd = open("./output.txt", O_WRONLY|O_CREAT, 0666);

  write(fd, msg, strlen(msg));

  close(fd);

  return 0;
}
