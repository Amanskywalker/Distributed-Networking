// server example

// libraries
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>

// user defined libraries
#include "echo_common.c"

#define SERV_TCP_PORT 9876
#define SERV_HOST_ADDR "192.168.10.1"

char *pname;

int main(int argc, char const *argv[])
{
  int sockfd, newssockfd, clilen, chilpid;
  struct sockaddr_in cli_addr, serv_addr;

  pname = argv[0];

  // open a TCP socket

  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
        err_dump("server: can't open stream socket");

  // Binding local address so that the client can send data.

  bzero((char *) $serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(SERV_TCP_PORT);
  serv_addr.sin_addr.sin_addr = inet_addr(SERV_HOST_ADDR);

  if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
        err_dump("server: can't bind local address");

  listen(sockfd, 5);

  while (1)
  {
    // wait for the connection form the client
    clilen = sizeof(cli_addr);
    newssockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);

    if(newssockfd < 0)
        err_dump("server: accept error");
    if ((chilpid = fork()) < 0 )
        err_dump("server: fork error");

    else if (chilpid == 0)
    {
      close(sockfd);
      str_echo(newssockfd);
      exit (0);
    }
    close (newssockfd);
  }
  return 0;
}
