#ifndef KQUEUE_HPP
# define KQUEUE_HPP
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <map>
class Kqueue
{
public:
  static const int MAX_CHANGE = 5000;
  static const int MAX_EVENT = 5000;
  Kqueue(){}
  ~Kqueue() {close(kqueue_fd_);}
  void  KqueueStart(const int &serv_sock);
  void ChangeEvent(int ident, int filter, int flags, void *udata);

private:
  std::vector<struct kevent> change_list_;
	struct kevent event_list_[8];
	std::map<int, string> clients_;
	int kqueue_fd_;
};

#endif
