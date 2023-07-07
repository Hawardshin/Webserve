#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// 1. 소켓 열기
// 2. 바인드하기
// 3. listen하기
// 4. accept하기
// 5. select 함수로 이벤트 등록하기

class selectServ
{
  private :
    int serv_sockfd;
    struct sockaddr_in serv_addr;
    socklen_t serv_addrsz;

    int clnt_sockfd;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addrsz;

    FILE *read;
    FILE *write;//입출력 스트림 분리
  public :
    void  sockInit(char* port)throw(std::runtime_error &);
    void  sockBind()throw(std::runtime_error &);
    void  sockListen()throw(std::runtime_error &);
    void  sockAccept()throw(std::runtime_error &);
};

void  selectServ::sockInit(char* port)throw(std::runtime_error&){
  serv_sockfd = socket(PF_INET, SOCK_STREAM, 0);
  if (serv_sockfd == -1)
    throw(std::runtime_error("SOCK() ERROR"));
  std::memset(&serv_addr,0,sizeof(serv_addr));
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(std::atoi(port));
  serv_addr.sin_family = AF_INET;
  serv_addrsz = sizeof(serv_addr);
}

void  selectServ::sockBind() throw(std::runtime_error &){
  if (bind(serv_sockfd, (sockaddr *)&serv_addr, serv_addrsz) == -1)
    throw(std::runtime_error("BIND() ERROR"));
}

void  selectServ::sockListen()throw(std::runtime_error &){
  if (listen(serv_sockfd, 15) == -1)
    throw(std::runtime_error("LISTEN() ERROR"));
}

void   selectServ::sockAccept() throw(std::runtime_error &){
  clnt_addrsz = sizeof(clnt_addr);
  clnt_sockfd = accept(serv_sockfd, (struct sockaddr *) &clnt_addr, &clnt_addrsz);
  if (clnt_sockfd == -1)
    throw(std::runtime_error("ACCEPT() ERROR"));
}

int main(int argc, char**argv)
{
  try
  {
    if (argc != 2)
      throw(std::invalid_argument("YOU MUST INPUT PORT NUM!"));
    selectServ s1;
    s1.sockInit(argv[1]);
    s1.sockBind();
    s1.sockListen();
    s1.sockAccept();
  }
  catch(std::exception &e){
    std:: cerr << e.what() << "\n";
  }
}
