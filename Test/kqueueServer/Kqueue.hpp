#ifndef KQUEUE_HPP
# define KQUEUE_HPP
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <unistd.h>
#include <iostream>
class Kqueue
{
public:
  static const int MAX_CHANGE = 5000;
  static const int MAX_EVENT = 5000;
  Kqueue(): changes_n_(0){}
  ~Kqueue() {close(kqueue_fd_);}
  void  KqueueStart(const int &serv_sock);
  void ChangeEvent(int nIdent, int nFilter, int nFlags, void * pUdata );

private:
  int kqueue_fd_;
  struct kevent change_list_[MAX_CHANGE];
  int changes_n_;
  struct kevent event_list_[MAX_EVENT];

};

#endif
