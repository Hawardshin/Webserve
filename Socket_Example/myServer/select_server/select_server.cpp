#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <sys/time.h>
#include <fcntl.h>


// 1. 소켓 열기
// 2. 바인드하기
// 3. listen하기
// 4. accept하기
// 5. select 함수로 이벤트 등록하기
//클라이언트 숫자를 몇명까지 하는게 맞는걸까?
//애당초 숫자를 지정하지 않는건가?
class selectServ
{
  public :
    static const int BUFF_SIZE = 500;
    ~selectServ();
    void  sockInit(char* port);
    void  sockBind();
    void  sockListen();
    void  sockAccept();

    void  selectDetectEvent();
  private :
    char buff[BUFF_SIZE];
    //서버 소켓
    int serv_sockfd;
    struct sockaddr_in serv_addr;
    socklen_t serv_addrsz;

    //클라이언트 소켓
    int clnt_sockfd;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addrsz;

    int fd_max; // 0부터 클라이언트 접속할때마다 하나씩 늘어간다.

    //이벤트 처리 인자들
    fd_set read_fd_set;
    fd_set write_fd_set;
    fd_set except_fd_set;
    timeval time_out;//select timeout

    //입출력 스트림 분리
    // FILE *read;
    // FILE *write;
};

void  selectServ::sockInit(char* port){
  serv_sockfd = socket(PF_INET, SOCK_STREAM, 0);
  if (serv_sockfd == -1)
    throw(std::runtime_error("SOCK() ERROR"));

  std::memset(&serv_addr,0,sizeof(serv_addr));
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(std::atoi(port));
  serv_addr.sin_family = AF_INET;
  serv_addrsz = sizeof(serv_addr);
  fd_max = 0;
  FD_ZERO(&read_fd_set);
}

void  selectServ::sockBind() {
  if (bind(serv_sockfd, (sockaddr *)&serv_addr, serv_addrsz) == -1)
    throw(std::runtime_error("BIND() ERROR"));
}

void  selectServ::sockListen(){
  if (listen(serv_sockfd, 15) == -1)
    throw(std::runtime_error("LISTEN() ERROR"));
}

//resgister to fd_set variable
void   selectServ::sockAccept(){
  clnt_addrsz = sizeof(clnt_addr);
  clnt_sockfd = accept(serv_sockfd, (struct sockaddr *) &clnt_addr, &clnt_addrsz);
  if (clnt_sockfd == -1)
    throw(std::runtime_error("ACCEPT() ERROR"));
  FD_SET(clnt_sockfd, &read_fd_set);
  if (fd_max < clnt_sockfd)
    fd_max = clnt_sockfd;
}

void  selectServ::selectDetectEvent(){

  time_out.tv_sec = 5;
  time_out.tv_usec =5000;
  fd_set tmp = read_fd_set;
  int fd_num = select(fd_max+1, &tmp, 0,0, &time_out);
  if (fd_num == -1)
    throw(std::runtime_error("SELECT() ERROR!"));
  if (fd_num == 0)//timeout
  {
    std::cout << "TimeOut!! Waiting...\n";
    return ;
  }
  for(int i=0; i <fd_max + 1;i++)
  {
    if (FD_ISSET(i, &tmp))
    {
      if (i == serv_sockfd) //connection request
        sockAccept();
      else // read_message
      {
        int str_len = read(i, buff, BUFF_SIZE);
        if (str_len == 0) // close request
        {
          FD_CLR(i, &read_fd_set);
          close(i);
          std::cout << "CLOSE CLIENT : " << i << "\n";
        }
        else
          write(i, buff, str_len);//echo server;
      }
    }
  }
}

 selectServ::~selectServ(){
  close(serv_sockfd);
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
    while (1)
    {
      s1.sockAccept();
    }
  }
  catch(std::exception &e){
    std:: cerr << e.what() << "\n";
  }
}
