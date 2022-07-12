#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include "slowPrint.h"

int main()
{
  int pid;
  
  sem_t* sem;
  sem = sem_open("/hoge", O_CREAT, 0666, 0);

  char msg[256];
  sprintf(msg, "parent process(pid=%d)\n" , getpid());

  printf("before fork().\n");
  sem_wait(sem);		// P操作

  if((pid = fork()) == 0) {
    sprintf(msg, "child process(pid=%d)\n" , getpid());
  
    sem_wait(sem);		// P操作
    slowPrint(msg, 100000);	// CS
    //    sem_post(sem);		// V操作

    _exit(0);			// 子プロセス終了
  }

  sem_wait(sem);		// P操作
  slowPrint(msg, 100000);	// CS
  //  sem_post(sem);		// V操作

  wait(0);			// 子プロセスの終了待ち

  printf("after wait().\n");
  sem_wait(sem);		// P操作

  sem_unlink("/hoge");		// セマフォの削除

}
