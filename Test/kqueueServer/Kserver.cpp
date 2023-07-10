#include "Kserver.hpp"

/**
     * @brief Construct a new Kserver object
     *
     * @param port
     * 포트번호 오류 시 -1을 port 멤버에 초기화
     * @warning 중복 포트 번호 사용시 꺼짐
*/
Kserver::Kserver(char *port) {
  port_ = 0;
  if (port == NULL)
    port_ = -1;
  int num = 0;
  int i;

  for (i=0; port[i] != '\0';i++)
  {
    num *= 10;
    if (!isdigit(port[i]))
    {
      port_ = -1;
      return ;
    }
    num += (port[i]-'0');
  }
  if (i >= 10)
    port_ = -1;
  else
    port_ = num;
  std::cout << "Port : " << port_ << "\n";
}

/**
 * @brief Destroy the Kserver:: Kserver object
 * @todo 종료시 열어둔 port 및 fd를 수거해줘야 합니다.
 *
 */
Kserver::~Kserver() {
  close(serv_sockfd_);
}

/**
 * @brief sock(), bind(), listen()
 * @warning it can throw runtime_error, invalid_argument
 *
 */
void  Kserver::Server_init(){
  sockInit();
  sockBind();
  sockListen();
	kqueue_.KqueueStart(serv_sockfd_);//kqueue 시작
	kqueue_.ChangeEvent(serv_sockfd,server_socket, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL); );
	//kqueue에 서버소켓 fd등록

}
/**
 * @brief accept 함수 호출합니다. 호출된 clnt_sockfd에 accept된 fd가 있어서 그것들에 대한 처리가 필요합니다.
 *
 */
void  Kserver::sockAccept(){

  clnt_addrsz_ = sizeof(clnt_addr_);
  clnt_sockfd_ = accept(serv_sockfd_, (struct sockaddr *) &clnt_addr_, &clnt_addrsz_);
  if (clnt_sockfd_ == -1)
    throw(std::runtime_error("ACCEPT() ERROR"));
  std::cout << "Connected Client : " << clnt_sockfd_ << "\n";
}

/**
 * @brief use sock() to server socket
 * @warning if port is invalid throw invalid_argument
 *
 */
void  Kserver::sockInit(){
  if (port_ == -1)
    throw(std::invalid_argument("Port Num is not vaild"));
  serv_sockfd_ = socket(PF_INET, SOCK_STREAM, 0);
  if (serv_sockfd_ == -1)
    throw(std::runtime_error("SOCK() ERROR"));
}

/**
 * @brief serv_addr init and Bind()
 *
 */
void  Kserver::sockBind(){
  std::memset(&serv_addr_,0,sizeof(serv_addr_));
  serv_addr_.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr_.sin_port = htons(port_);
  serv_addr_.sin_family = AF_INET;
  if (bind(serv_sockfd_, (struct sockaddr *)&serv_addr_,sizeof(serv_addr_)) == -1)
    throw(std::runtime_error("BIND() ERROR"));
}

/**
 * @brief listen() 연결 요청 대기 큐 15개
 * @note 여기서 서버 fd를 non-blocking으로 바꿔줍니다.
 *
 */
void  Kserver::sockListen(){
  if (listen(serv_sockfd_, 15) == -1)
    throw(std::runtime_error("LISTEN() ERROR"));
	fcntl(serv_sockfd_, F_SETFL, O_NONBLOCK);
}


