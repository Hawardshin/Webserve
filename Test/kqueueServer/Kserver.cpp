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
	kqueue_.ChangeEvent(serv_sockfd_, EVFILT_READ, EV_ADD | EV_ENABLE, NULL);//kqueue에 서버소켓 readEvent 등록
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


 void  Kserver::startWorking()
 {
  while (1)
  {
    kqueue_.KqueueStart(serv_sockfd_);
    event_list_size_ = kqueue_.detectEvent(event_list_);
    handleEvents();
  }
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

void  Kserver::handleEvents()
{
  struct kevent *cur_event;
  for(int i=0;i < event_list_size_;i++)
  {
    cur_event = &event_list_[i];
    if (cur_event->filter ==  EVFILT_READ)
    {
      if (cur_event->ident == serv_sockfd_)
        registerNewClnt();
      else//client-socket
        clntSockReadable(cur_event);
    }
    else if (cur_event->filter == EVFILT_WRITE) //ONLY CLIENT
    {
      std::map<int, std::string>::iterator it = clnt_data_store_.find(cur_event->ident);
      if (it != clnt_data_store_.end())
      {
          if (clnt_data_store_[cur_event->ident] != "")
          {
              int n = write(cur_event->ident, clnt_data_store_[cur_event->ident].c_str(),clnt_data_store_[cur_event->ident].size());
              if (n == -1)
              {
                  std::cerr << "client write error!" << "\n";
                  disconnectClient(cur_event->ident);
              }
              else
                  clnt_data_store_[cur_event->ident].clear();
          }
      }
    }
    else
      throw("THAT'S IMPOSSIBLE THIS IS CODE ERROR!!");
  }
}


void  Kserver::registerNewClnt()
{
  clnt_addrsz_ = sizeof(clnt_addr_);
  clnt_sockfd_ = accept(serv_sockfd_,  (struct sockaddr *) &clnt_addr_, &clnt_addrsz_);
  if (clnt_sockfd_ == -1)
    throw(std::runtime_error("ACCEPT() ERROR"));
  std::cout << "Connected Client : " << clnt_sockfd_ << "\n";
  fcntl(clnt_sockfd_, F_SETFL, O_NONBLOCK);
  kqueue_.ChangeEvent(clnt_sockfd_, EVFILT_READ, EV_ADD | EV_ENABLE, NULL);
  kqueue_.ChangeEvent(clnt_sockfd_, EVFILT_WRITE, EV_ADD | EV_ENABLE, NULL);
  clnt_data_store_[clnt_sockfd_] = "";
}

/**
 * @brief client socket is in a readable state
 *
 */
void  Kserver::clntSockReadable(struct kevent *cur_event)
{
  if (clnt_data_store_.find(cur_event->ident) == clnt_data_store_.end())
    throw("INVALID CLIENT_SOCKET() (It's impossible)");
  int rlen = read(cur_event->ident ,buff_, BUFF_SIZE);
  if (rlen == -1)
    throw(std::runtime_error("READ() ERROR!! IN CLNT_SOCK"));
  buff_[rlen] = '\0';
  clnt_data_store_[cur_event->ident] += buff_;
  std::cout << "FROM CLIENT NUM " << cur_event->ident << ": " << clnt_data_store_[cur_event->ident] << "\n";
}

void  Kserver::disconnectClient(int clnt_fd)
{
  std::cout << "CLINET DISCONNECTED:: " << clnt_fd << "\n";
  close(clnt_fd);
  clnt_data_store_.erase(clnt_fd);
}
