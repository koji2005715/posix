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
  sem = sem_open("/hoge", O_CREAT, 0666, 1);

  char msg[256];
  sprintf(msg, "parent process(pid=%d), ptr=%p\n" , getpid(), msg);

  if((pid = fork()) == 0) {
    // 子プロセス
    sprintf(msg, "child process(pid=%d), ptr=%p\n" , getpid(), msg);
  
    sem_wait(sem);		// P操作
    slowPrint(msg, 100000);	// CS
    sem_post(sem);		// V操作

    //    sem_close(sem);
    //    _exit(0);			// 子プロセス終了
  }

  // 親プロセス

  sem_wait(sem);		// P操作
  slowPrint(msg, 100000);	// CS
  sem_post(sem);		// V操作

  wait(0);			// 子プロセスの終了待ち
  sem_unlink("/hoge");		// セマフォの削除

}
