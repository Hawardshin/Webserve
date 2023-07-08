#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <exception>
#include <vector>

class Server
{
  private :
    int sockfd;
    struct sockaddr_in serv_adr;
    struct sockaddr_in client_adr;
    socklen_t clnt_adr_sz;
    int client_sock;
    int operand_num;
    std::vector<double> data;
    char operand;
    double result;//div by 0 ,overflow 해결
  public :
    void  initServerSock();// sockfd init
    void  bindingSocket(char *port_num) throw(std::runtime_error&); //connet_fd 에 connet socket bind
    void  listenSocket()throw(std::runtime_error&); // socket이 listen 하고 있습니다.
    void  acceptSocket()throw(std::runtime_error&);
    void  Parse_by_client(); // 들어오는 첫번째 입력은 갯수, 두번째부터 쭉 저장. 마지막은 연산자
    void  Calc()throw(std::runtime_error&);//계산 진행
    void  sendToClient(); //클라이언트에게 계산 결과를 보냅니다.
};


void  Server::initServerSock(){
  sockfd = socket(PF_INET, SOCK_STREAM,0);
  clnt_adr_sz = sizeof((client_adr));
}

void  Server::bindingSocket(char *port_num)throw(std::runtime_error&){
  std::memset(&serv_adr, 0, sizeof(serv_adr));
  serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_adr.sin_family = AF_INET;
  serv_adr.sin_port = htons(std::atoi(port_num));
  if (bind(sockfd, (struct sockaddr *) &serv_adr,sizeof(serv_adr)) == -1)
    throw(std::runtime_error("Server:: bind() error\n"));
}

void  Server::listenSocket() throw(std::runtime_error&){
  if (listen(sockfd,5) == -1)
    throw(std::runtime_error("Server:: listen() error\n"));
}
void  Server::acceptSocket() throw(std::runtime_error&){
  client_sock = accept(sockfd, (struct sockaddr *) &client_adr, &clnt_adr_sz);
  if (client_sock == -1)
    throw(std::runtime_error("Server:: accept() error\n"));
}
void  Server::Parse_by_client(){
   read(client_sock,&operand_num,sizeof(operand_num));
   for(int i=0; i < operand_num;i++){
    double tmp;
    read(client_sock,&tmp,sizeof(tmp));
    data.push_back(tmp);
   }
  read(client_sock,&operand,sizeof(operand));
}

void  Server::Calc()throw(std::runtime_error&)
{
  result = 0;
  switch(operand){
    case ('+') :
      for (int i=0;i < operand_num;i++){
        result += data[i];
      }
      break;
    case ('/') :
      for (int i=0;i < operand_num;i++){
        result /= data[i];
      }
      break;
    case ('-') :
      for (int i=0;i < operand_num;i++){
        result -= data[i];
      }
      break;
    case ('*') :
     for (int i=0;i < operand_num;i++){
        result *= data[i];
      }
      break;
    default : throw(std::runtime_error("NOT ALLOW OPERATOR\n"));
  }
}
void  Server::sendToClient(){
  write(client_sock,&result, sizeof(result));
  close(client_sock);
}
int main(int argc, char**argv)
{
  if (argc!= 2){
    std::cerr << "error : <port>\n";
    return (1);
  }
  Server s1;
  try
  {
      s1.initServerSock();
      s1.bindingSocket(argv[1]);
      s1.listenSocket();
      s1.acceptSocket();
      s1.Parse_by_client();
      s1.Calc();
      s1.sendToClient();
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }

}
