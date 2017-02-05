// standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// the Networking libraries
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

// to display the message on failure
#define handle_error(msg) \
   do { perror(msg); exit(EXIT_FAILURE); } while (0)


int debug=1;

int main(int argc, char const *argv[])
{
  int SocketDescriptor;
  SocketDescriptor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  //testing only
  if (debug)
  {
    printf("%d\n",SocketDescriptor);
    if (SocketDescriptor == -1)
      handle_error("socket");
  }

  struct sockaddr_in *myaddr;    // address structure
  int addrlen;                // address length

  int BindTemp;               // to temproraly store the value returned by the the bind routine

  memset(&myaddr, 0, sizeof(struct sockaddr_in)); // filling address with memory bytes

  addrlen = sizeof(struct sockaddr_in);

  BindTemp = bind(SocketDescriptor, myaddr, addrlen);
  // testing only
  if (debug)
  {
    printf("%d\n",BindTemp);
    if (BindTemp == -1)
      handle_error("bind");
  }

  return 0;
}


/* reference
/* Source http://linux.die.net/man/7/ip

struct sockaddr_in {
    sa_family_t    sin_family; //address family: AF_INET
    in_port_t      sin_port;   // port in network byte order
    struct in_addr sin_addr;   // internet address
};

// Internet address.
struct in_addr {
    uint32_t       s_addr;     // address in network byte order
};
