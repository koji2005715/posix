#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include "slowPrint.h"

int main(int argc, char** argv)
{
  int pid;
  
  sem_t* sem;
  sem = sem_open("/hoge", O_CREAT, 0666, 1);

  char msg[256];
  sprintf(msg, "This is %s. Now exec has executed. Check name of process(pid=%d)\n", argv[0], getpid());
  
  sem_wait(sem);		// P操作
  slowPrint(msg, 100000);	// CS
  sem_post(sem);		// V操作

  sem_close(sem);
}
