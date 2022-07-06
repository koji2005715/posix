#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HELLO_MR_SERVER "hello, Mr. server"

void sock_error()
{
  perror("");
  exit(1);
}

int main()
{
  int s;
  struct hostent * hp;
  struct sockaddr_in a;
  short port = 5000;
  char * buffer = HELLO_MR_SERVER;
  int len = strlen(buffer) + 1;

  //declaration
  if (-1 == (s = socket(AF_INET, SOCK_STREAM, 0))) 
    sock_error();

  /* get server address */
  if (0 == (hp = gethostbyname("localhost")))
    sock_error();

  /* connect to server */
  a.sin_family = AF_INET;
  a.sin_addr.s_addr = *((unsigned long *)hp->h_addr);
  a.sin_port = htons(port);

  printf("connecting to server localhost:%d\n", port);
  if (-1 == connect(s, (struct sockaddr *)&a, sizeof(a)))
    sock_error();

  printf("sending\n");
  if (len != send(s, buffer, len, 0))
    sock_error();

  printf("done\n");
}
