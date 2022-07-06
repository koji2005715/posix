// ポーリング版

#include <ncurses.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <semaphore.h>

#define SIZE 512

int *addr;
int *nprocess;
int *x;
int *y;
int *pid;

sem_t *sem;

int main()
{
  int fd;

  sem = sem_open("/hoge", O_CREAT, 0666, 1);

  sem_wait(sem); {
    fd = shm_open("/hoge", O_CREAT | O_RDWR, 0666);
    ftruncate(fd, SIZE);
    addr = (int*)mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    nprocess = addr;
    x = addr + 1;
    y = addr + 2;
    pid = addr + 3;

    pid[*nprocess] = getpid();
    (*nprocess)++;
    printf("%d process(es) attached.\n", *nprocess);
    for (int n = 0; n < *nprocess; n++)
      printf("pid=%d\n", pid[n]);
  } sem_post(sem);

  sleep(1);

  initscr();
  curs_set(0);
  cbreak();
  noecho();
  nodelay(stdscr, true); // キー入力待ちをしない．
  keypad(stdscr, true);

  int key;
  do {
    key = getch();

    sem_wait(sem); {
      switch (key) {
      case KEY_UP:    (*x)--; break;
      case KEY_DOWN:  (*x)++; break;
      case KEY_LEFT:  (*y)--; break;
      case KEY_RIGHT: (*y)++; break;
      }
      move(*x, *y);
    } sem_post(sem);

    echochar('*');

  } while(key != 'q');

  endwin();

  int np;
  sem_wait(sem); {
    np = --(*nprocess);
    printf("%d process(es) left\n", np);
    munmap(addr, SIZE);
    if (np == 0) {
      shm_unlink("/hoge");
      printf("shared memory was removed.\n");
    }
  } sem_post(sem);

  if (!np)
    sem_unlink("/hoge");

  close(fd);
  
  return 0;
}
