#include <stdio.h>
#include <unistd.h>

void slowPrint(const char *msg, unsigned int us)
{
  while(*msg) {
    putchar(*msg);
    fflush(stdout);
    usleep(us);
    msg++;
  }
}
