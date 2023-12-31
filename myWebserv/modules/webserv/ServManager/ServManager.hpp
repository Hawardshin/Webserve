#ifndef SERVMANAGER_HPP
# define SERVMANAGER_HPP
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
#include "./Kqueue/Kqueue.hpp"


class ServManager{
public:
	static const int BUFF_SIZE = 500;
	ServManager();
	~ServManager();

private:
		LoopManager loop_manager_;
		std::map<int, Client> clnt_store_;//미정
		Kqueue kqueue_;
		struct kevent event_list_[8];//한번 감지된 이벤트의 배열
		int event_list_size_;
		char buff_[BUFF_SIZE];
		std::vector<int> serv_port_;
};

#endif
