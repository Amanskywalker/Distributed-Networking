// this hold the common function in both the server and client programs

// libraries

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
int writen(int fd, char *ptr, nbytes)
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

#define MAXLINE 512

str_echo(int stockfd)
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
