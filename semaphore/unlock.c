#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>

int main()
{
  sem_t* sem;
  sem = sem_open("/hoge", 0);

  sem_post(sem);
  sem_close(sem);
}
