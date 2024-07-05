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


  if((pid = fork()) == 0) {
    
    sprintf(msg, "Here is child process after fork() before exec().\nWatch the name of process(pid=%d) in output of top command.\n", getpid());

    sem_wait(sem);		// P操作
    slowPrint(msg, 100000);	// CS
    sem_post(sem);		// V操作

    sem_close(sem);

    execlp("./fuga", "./fuga", NULL); // プロセスの置き換え

    _exit(0);			// 子プロセス終了（実行されない）
  }

  // 親プロセス
  sprintf(msg, "Here is parent process(pid=%d).\n" , getpid());

  sem_wait(sem);		// P操作
  slowPrint(msg, 100000);	// CS
  sem_post(sem);		// V操作

  wait(0);			// 子プロセスの終了待ち
  sem_unlink("/hoge");		// セマフォの削除

}
