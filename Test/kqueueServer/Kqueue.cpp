#include "Kqueue.hpp"

void  Kqueue::KqueueStart(const int &serv_sock)
{
  kqueue_fd_ = kqueue();
  if (kqueue_fd_ == -1)
    throw(std::runtime_error("kqueue() ERROR!!"));

}

/**
 * @brief 이벤트를 등록하는 함수
 *
 * @param ident 이벤트를 감시할 대상에 대한 fd
 * @param filter 이벤트 필터 플래그 EVFILE_READ,EVFILT_WRITE
 * @param flags EV_ADD,EV_ENABLE,EV_DISABLE,EV_DELETE,EV_ONESHOT
 * @param udata 일반적으로 NULL
 * @note flags : EV_ADD ,EV_ENABLE (이벤트를 추가/활성화)
 *  EV_DISABLE, EV_DELETE(이벤트 비활성화 삭제),
 *  EV_ONESHOT(설정된 이벤트를 한번만 알려준다)
 */
void Kqueue::ChangeEvent(int ident, int filter, int flags, void * udata)
{
  EV_SET( &change_list_[changes_n_], ident, filter, flags, 0, 0, udata );
  changes_n_++;
}
