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

  if((pid = fork()) == 0) {
    // 子プロセス
    char msg[256];
    sprintf(msg, "critical section in child process(pid=%d)\n" , getpid());
  
    sem_wait(sem);		// P操作
    slowPrint(msg, 100000);	// CS
    sem_post(sem);		// V操作

    sem_close(sem);

    _exit(0);			// 子プロセス終了
  }

  // 親プロセス
  char msg[256];
  sprintf(msg, "critical section in parent process(pid=%d)\n" , getpid());

  sem_wait(sem);		// P操作
  slowPrint(msg, 100000);	// CS
  sem_post(sem);		// V操作

  wait(0);			// 子プロセスの終了待ち
  sem_unlink("/hoge");		// セマフォの削除

}
