#include <unistd.h>
#include "slowPrint.h"

int main()
{
  int pid;

  if((pid = fork()) == 0) {
    // child process
    slowPrint("This is a pen.\n", 200000);
    _exit(0);
  }

  // parent process
  slowPrint("Hello, World!\n", 200000);
}
