#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define HELLO_MR_SERVER "hello, Mr. server"

void sock_error()
{
  perror("");
  exit(1);
}

int main()
{
  int s, new_s;
  int l;
  struct sockaddr_in a;
  /* make socket */
  if (-1 == (s = socket(AF_INET, SOCK_STREAM, 0)))
    sock_error();

  /* assign port */
  a.sin_family = AF_INET;
  a.sin_addr.s_addr = INADDR_ANY;
  a.sin_port = htons(5000);
  if (-1 == bind(s, (struct sockaddr *)&a, sizeof(a)))
    sock_error();

  /* specify queue length */
  if (-1 == listen(s, 1)) 
    sock_error();

  l = sizeof(a);
  if (-1 == getsockname(s,  (struct sockaddr *)&a, &l)) 
    sock_error();
  
  printf("accepting connection at port %d...\n", ntohs(a.sin_port));
  l = sizeof(a);
  if (-1 == (new_s = accept(s, (struct sockaddr *)&a, &l))) 
    sock_error();

  {
    /* now ready to receive stuff */
    char buffer[100];
    int expect_len = strlen(HELLO_MR_SERVER) + 1;
    printf("receiving\n");
    if (expect_len != recv(new_s, buffer, expect_len, 0))
      sock_error();
    printf("received: %s\n", buffer);
    printf("done\n");
  }

  return 0;
}
