// シグナル（ソフトウェア割り込み）版

#include <ncurses.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include <signal.h>

#define SIZE 512

int* addr;
int* nprocess;
int* x;
int* y;
int *pid;

sem_t *sem;

void draw(void)
{
  sem_wait(sem); {
    move(*x, *y);
  } sem_post(sem);
  echochar('*');
}

void signal_handler(int signum)
{
  if (signum == SIGUSR1)
    draw();
}

void init_signal(void)
{
  struct sigaction sa;
  memset(&sa, 0, sizeof(sa));
  sa.sa_handler = signal_handler;
  sa.sa_flags = SA_RESTART;
  sigaction(SIGUSR1, &sa, NULL);
}

int main()
{
  int fd;

  sem = sem_open("/hoge", O_CREAT, 0666, 1);

  sem_wait(sem); {
    fd = shm_open("/hoge", O_CREAT | O_RDWR, 0666);
    ftruncate(fd, SIZE);
    addr = (int*)mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    nprocess = addr;
    x = addr+1;
    y = addr+2;
    pid = addr + 3;

    pid[*nprocess] = getpid();
    (*nprocess)++;
    printf("%d process(es) attached.\n", *nprocess);
    for (int n = 0; n < *nprocess; n++)
      printf("pid=%d\n", pid[n]);
  } sem_post(sem);

  sleep(1);

  init_signal();

  initscr();
  curs_set(0);
  cbreak();
  noecho();
  nodelay(stdscr, false); // キー入力待ちをする
  keypad(stdscr, true);

  draw();
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
    } sem_post(sem);

    for (int n = 0; n < *nprocess; n++)
      kill(pid[n], SIGUSR1);

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
