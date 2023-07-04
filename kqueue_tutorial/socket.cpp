#include <sys/socket.h>
#include <sys/un.h>
#include <netdb.h>
#include  <cstring>
#include <err.h>
//메인 이벤트 루프는 클라이언트가 연결을 끊은 경우 accept(2) 또는 close(2)를 호출하여 수신 소켓의 이벤트에 반응합니다.
//시작하려면 먼저 소켓을 생성한 다음 주소에 바인딩합니다.
int main(){
  struct addrinfo *addr;
  struct addrinfo hints;

  /* open a TCP socket */
  memset(&hints, 0, sizeof hints);
  hints.ai_family = PF_UNSPEC; /* any supported protocol */
  hints.ai_flags = AI_PASSIVE; /* result for bind() */
  hints.ai_socktype = SOCK_STREAM; /* TCP */
  int error = getaddrinfo ("127.0.0.1", "8080", &hints, &addr);
  if (error)
      errx(1, "getaddrinfo failed: %s", gai_strerror(error));
}
//getaddrinfo(3)는 제공된 호스트 이름과 일치하는 주소 배열에 대한 포인터를 가져왔는데, 여기서는 첫 번째 일치하는 것만 사용하겠습니다.
