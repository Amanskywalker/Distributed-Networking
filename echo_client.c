// client example

// libraries
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>

// user defined libraries
#include "echo_common.h"

#define SERV_TCP_PORT 9876
#define SERV_HOST_ADDR "127.0.0.1"

char *pname;

int main(int argc, char const *argv[])
{
  int sockfd;
  struct sockaddr_in serv_addr;

  pname = argv[0];

  // fill the structure "serv_addr" with the address of the server that we wants to connect with

  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr(SERV_HOST_ADDR);
  serv_addr.sin_port = htons(SERV_TCP_PORT);

  // open TCP socket

  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
      err_sys("client: can't open stream socket");

  // connet to the server

  if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
      err_sys("client: can't connet to server");

  str_cli(stdin, sockfd);         // do it all

  close(sockfd);

  return 0;
}
