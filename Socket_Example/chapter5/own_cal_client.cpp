#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <exception>


#define BUF_SIZE 1024

class Client
{
  private :
    int sockfd;
    char message[BUF_SIZE];
    int str_len, recv_len, recv_cnt;
    struct sockaddr_in serv_adr;
  public :
    void  initServAdr(char *ip_ad, char* port);
    void  make_sock();
    const int& getSock();
    void  Connet_with_server()throw(std::runtime_error&);
    void  sendData();
};

void Client:: initServAdr(char *ip_ad, char* port){
  std::memset(&serv_adr, 0,sizeof(serv_adr));
  inet_aton(ip_ad, &serv_adr.sin_addr);
  serv_adr.sin_family = AF_INET;
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
}

void  Client::sendData()
{
  str_len = 0
  int operand_num;
  std::cin >> opernad_num;
  int number;
  for (int i=0; i < operand_num;i++){
    std::cout << "Operand "<<  1:\n";
  }


  std::cin >> number
  str_len =write(sockfd, number,sizeof(number));
  std::cout << "Operand 2:\n";
  std::cin >> number
  str_len =write(sockfd, number,sizeof(number));
  std::cout << "Operand 3:\n";
  std::cin >> number
  str_len =write(sockfd, number,sizeof(number));
  char oper;
  std::cout << "Operator :\n";
  str_len =write(sockfd, oper,sizeof(oper));
}

void  Client::receiveStirng(){
  recv_len = 0;
  while (str_len < recv_len)
  {
    recv_len += read(sock, message, BUF_SIZE);
  }
  std::cout << message << "\n";
}

int main(int argc, char *argv[])
{
  if (argc != 3){
    std::cerr << "error : <ip> <port>\n";
    return (1);
  }
  Client s1;
  s1.initServAdr(argv[1], argv[2]);
  s1.make_sock();
  s1.Connet_with_server();
  s1.sendData()


}
