#ifndef ECHO_COMMON_H
#define ECHO_COMMON_H

// this hold the common function in both the server and client programs

// libraries
#include <stdio.h>

// to print erroes
void err_sys(const char* x)
{
    perror(x);
    exit(1);
}

// to print dump
void err_dump(const char* x)
{
    perror(x);
    exit(1);
}

// read "n" bytes from the descriptor
// Use in the place of read() when fd is a stream socket
int readn(int fd, char ptr, int nbytes)
{
  int nleft, nread;
  nleft = nbytes;

  while(nleft > 0)
  {
    nread = read(fd, ptr, nleft);
    if (nread < 0)
        return (nread);           // error, return < 0
    else if (nread == 0)
        break;                    // EOF encounter

    nleft -= nread;
    ptr += nread;
  }
  return (nbytes - nleft);        // return >=0
}

// write "n" bytes to a descriptor
// use in place of write() when fd is a stream socket
int writen(int fd, char *ptr, int nbytes)
{
  int nleft, nwritten;
  nleft = nbytes;

  while (nleft > 0)
  {
    nwritten = write(fd, ptr, nleft);
    if (nwritten <= 0)
          return nwritten;              // error

    nleft -= nwritten;
    ptr += nwritten;
  }
  return (nbytes - nleft);
}

/*
  Read a line from a descriptor. Read the line one byte at a time, looking for the newline. Then newline is stored in the buffer,
  then follow it with a null, returns the number of characters up to, but not including, the null
*/

int readline(int fd, char *ptr, int maxlen)
{
  int n, rc;
  char c;
  for (n = 1; n < maxlen; n++)
  {
    if ((rc= read(fd, &c, 1)) == 1)
    {
      *ptr++ = c;
      if(c == '\n')
          break;
    }
    else if (rc == 0 )
    {
      if (n == 1)
        return 0 ;      // EOF, no data read
      else
        break ;         // EOF, some data was read
    }
    else
        return (-1);    // error
  }

  *ptr = 0;
  return (n);

}

#define MAXLINE 512

str_echo(int sockfd)
{
  int n;
  char line[MAXLINE];

  while (1)
  {
    n = readline(sockfd, line, MAXLINE);
    if (n == 0)
        return;       // connetion terminated
    else if (n < 0)
        err_dump("str_echo : readline error");

    if(writen (sockfd, line, n) != n)
        err_dump("str_echo : writen error");
  }
}

/*
  Read the contents of the FILE *fp, write each line to the stream socket (to the server),
  then read a line back from the socket and write it to the standard output
*/

str_cli(int *fd, int sockfd)
{
  int n;
  char sendline[MAXLINE], recvline[MAXLINE];

  while (fgets(sendline, MAXLINE, fd) != NULL)
  {
    n = strlen(sendline);
    if (writen (sockfd, sendline, n) != n)
        err_sys("str_cli : writen error on socket");
    // now read a line form the socket and write it to the standard output

    n = readline(sockfd, recvline, MAXLINE);
    if (n < 0)
        err_dump("str_cli: readline error");

    recvline[n] = 0;
    fputs(recvline, stdout);
  }

  if (ferror(fd))
    err_sys("str_cli: error reading file");
}

#endif
