#include <sys/types.h>
#include <sys/wait.h>
#include <string>
#include "Monitor.h"
#include "slowPrint.h"

using namespace std;

class Display : public Monitor {
  string msg;
  unsigned int us;
  bool wait_enter;

 public:
  Display(const char* name, unsigned int value = 1) : Monitor(name, value) {}
  
  void setMessage(const string& _msg, unsigned int _us, bool _wait_enter = false) {
    msg = _msg;
    us = _us;
    wait_enter = _wait_enter;
  }

  void CS() {
    slowPrint(msg.c_str(), us);
    if (wait_enter) {
      printf(" [hit enter key]");
      while(getchar() != '\n')
	;
    } else
      printf("\n");
  }
};

Display display("/hoge");


void message(const string& msg, bool w = false)
{
  display.setMessage(msg, 50000, w);
  display.execute();
}

int main()
{
  string msg;

  int pid;

  message("P: before fork().", true);

  if ((pid = fork()) == 0) {
    message(string("C: after fork()(pid=") + to_string(getpid()) + ")");
    message("C: press enter to terminate", true);
    _exit(0);			// 子プロセス終了
  }

  message(string("P: after fork()(pid=") + to_string(getpid()) + ")");

  message("P: before wait(). waiting until the child process exits", true);
  wait(0);			// 子プロセスの終了待ち

  message("P: after wait(). the child process has terminated");
  message("P: press enter to terminate", true);
}
