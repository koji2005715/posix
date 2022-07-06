#include <sys/socket.h>
#include <netdb.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define SERVER_HOST "localhost"
#define SERVER_PORT "5000"

void sock_error()
{
  perror("");
  exit(1);
}

int main()
{
  int client_fd;
  struct addrinfo hints, *res;

  char buffer[100];
  int len;

  /* get server info */
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  if (getaddrinfo(SERVER_HOST, SERVER_PORT, &hints, &res) != 0)
    sock_error();

  //declaration
  if ((client_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1) 
    sock_error();

  /* connect to server */
  printf("connecting to server %s:%s\n", SERVER_HOST, SERVER_PORT);
  if (connect(client_fd, res->ai_addr, res->ai_addrlen) == -1)
    sock_error();
  printf("connected.\n");

  scanf("%s", buffer);

  len = strlen(buffer) + 1;
  printf("sending\n");
  if (len != send(client_fd, buffer, len, 0))
    sock_error();

  printf("done\n");

  close(client_fd);

  freeaddrinfo(res);
}
