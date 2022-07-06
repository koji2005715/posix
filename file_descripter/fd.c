#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
  char* buf = "abcdefg\n";
  write(0, buf, strlen(buf));
  write(1, buf, strlen(buf));
  write(2, buf, strlen(buf));
  write(3, buf, strlen(buf));
}
