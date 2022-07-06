#include <sys/socket.h>
#include <netdb.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>

#define SERVER_PORT "5000"

void sock_error()
{
  perror("");
  exit(1);
}

int main()
{
  int server_fd, client_fd;
  int l;
  struct addrinfo hints, *res;

  /* get server address */
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
  if (getaddrinfo(NULL, SERVER_PORT, &hints, &res) != 0)
    sock_error();

  struct sockaddr_in a;
  /* make socket */
  if ((server_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1)
    sock_error();

  /* assign port */
  if (bind(server_fd, res->ai_addr, res->ai_addrlen) == -1)
    sock_error();

  /* specify queue length */
  if (listen(server_fd, 1) == -1) 
    sock_error();

  while (1) {
    int n;

    l = sizeof(a);
    if (getsockname(server_fd,  (struct sockaddr *)&a, &l) == -1) 
      sock_error();

    printf("accepting connection at port %d...\n", ntohs(a.sin_port));
    l = sizeof(a);
    if ((client_fd = accept(server_fd, (struct sockaddr *)&a, &l)) == -1) 
      sock_error();

    /* now ready to receive stuff */
    char buffer[100];
    printf("receiving\n");
    if ((n = recv(client_fd, buffer, sizeof(buffer)-1, 0)) < 0)
      sock_error();
    printf("received: %s\n", buffer);
    printf("done\n");

    close(client_fd);

    if (buffer[0] == 'q')
      break;
  }

  sleep(1);

  close(server_fd);
  freeaddrinfo(res);

  return 0;
}
