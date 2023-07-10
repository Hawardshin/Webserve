#ifndef KSERVER_HPP
# define KSERVER_HPP
#include <sys/event.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <cstdio>
#include "kqueue.hpp"

/**
 * @brief kqueue using echo server
 *
 */
class Kserver{
  public :
    static const int BUFF_SIZE = 500;

    explicit Kserver(char *port);
    ~Kserver();
    void  Server_init();
    void  sockAccept();
    void  startWorking();
  private:
    Kserver();
    void  sockInit();
    void  sockBind();
    void  sockListen();
    void  handleEvents();
    void  registerNewClnt();
    void  clntSockReadable(struct kevent *cur_event);
    void  disconnectClient(int clnt_fd);
		Kqueue kqueue_;
    struct kevent event_list_[8];//한번 감지된 이벤트의 배열
    int event_list_size_;
    char buff_[BUFF_SIZE];
    int port_;

    //server socket
    int serv_sockfd_;
    struct sockaddr_in serv_addr_;
    socklen_t serv_addrsz_;

    //client socket
    int clnt_sockfd_;
    struct sockaddr_in clnt_addr_;
    socklen_t clnt_addrsz_;
    std::map<int, std::string> clnt_data_store_;
    //접속해있는 클라이언트 숫자.
    int clnt_num_;
};

#endif
