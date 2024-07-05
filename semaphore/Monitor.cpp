#include <fcntl.h>
#include <sys/stat.h>
#include "Monitor.h"

void Monitor::P() {
  sem_wait(sem);
}

void Monitor::V() {
  sem_post(sem);
}

Monitor::Monitor(const char* name, unsigned int value) : name(name)
{
  sem = sem_open(name, O_CREAT, 0666, value);
}

Monitor::~Monitor()
{
  sem_unlink(name);
}

void Monitor::execute() {
  P();
  CS();
  V();
}
			
