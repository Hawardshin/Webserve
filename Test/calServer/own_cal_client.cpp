#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <exception>
//클라이언트
//1. 피연산자 갯수 전달
//2. 피연산자 1개씩 입력 (따로 숫자가 아닌 값이 들어오는 예외는 처리하지 않음.)
//3. operator 전달.
//4. 전달이 끝나고 결과값을 받고 연결을 종료.

class Client
{
  private :
    int sockfd;
    struct sockaddr_in serv_adr;
  public :
    void  initServAdr(char *ip_ad, char* port);
    void  make_sock();
    const int& getSock();
    void  Connet_with_server()throw(std::runtime_error&);
    void  sendData();
    void  receiveResult();
    void  closeConnect();
};

void Client:: initServAdr(char *ip_ad, char* port){
  std::memset(&serv_adr, 0,sizeof(serv_adr));
  inet_aton(ip_ad, &serv_adr.sin_addr);
  serv_adr.sin_family = AF_INET;
  serv_adr.sin_port = htons(std::atoi(port));
}

void Client:: make_sock(){
  sockfd = socket(PF_INET, SOCK_STREAM, 0);
}

const int &Client:: getSock(){
  return (sockfd);
}

void  Client::Connet_with_server() throw(std::runtime_error&){
  if (connect(sockfd, (sockaddr *)&serv_adr, sizeof(serv_adr)) == -1)
    throw(std::runtime_error("connet error"));
  std::cout << "Connected:..............\n";
}

void  Client::sendData()
{
  std::cout << "Operand count: ";
  int operand_num;
  std::cin >> operand_num;
  double number;
  write(sockfd,&operand_num, sizeof(operand_num));
  for (int i=0; i < operand_num;i++){
    std::cout << "Operand "<< i << ": ";
    std::cin >> number;
    write(sockfd, &number,sizeof(number));
  }
  char oper;
  std::cout << "Operator : ";
  std::cin >> oper;
  write(sockfd, &oper,sizeof(oper));
}

void  Client::receiveResult(){
  double result_num;
  read(sockfd, &result_num, sizeof(result_num));
  std::cout <<"Operation result: " <<result_num << "\n";
}

void Client::closeConnect(){
  close(sockfd);
}

int main(int argc, char *argv[])
{
  if (argc != 3){
    std::cerr << "error : <ip> <port>\n";
    return (1);
  }
  try
  {
    Client s1;
    s1.initServAdr(argv[1], argv[2]);
    s1.make_sock();
    s1.Connet_with_server();
    s1.sendData();
    s1.receiveResult();
    s1.closeConnect();
  }
  catch(std::exception &e){
    std::cout << e.what() << "\n";
  }
}
