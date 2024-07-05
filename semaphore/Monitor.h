#pragma once
#include <semaphore.h>

class Monitor {
  sem_t* sem;
  const char* name;
 protected:
  void P();
  void V();
  virtual void CS() = 0;
 public:
  Monitor(const char* name, unsigned int value = 1);
  ~Monitor();
  void execute();
};
