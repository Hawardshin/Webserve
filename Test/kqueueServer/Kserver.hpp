#include <sys/event.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <cstdio>

//1.
class Kserver{
  public :
    Kserver();
    ~Kserver();
    int sock_fd;
    struct sockaddr_in serv_addr;
    struct sockaddr_in cln_addr;

  private:
};
