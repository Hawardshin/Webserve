#ifndef KSERVER_HPP
# define KSERVER_HPP


/**
 * @brief kqueue using echo server
 * @details <kqueue 동작 로직>
 * 1. kqeueu() 로 kqueue 생성
 * 2. eventSet을 이용해서 change_list_에 감지하고자 하는 이벤트의 갯수만큼 넣어준다.
 * 3. 처음에는 웹서버 소켓을 read에 대한 이벤트를 감지하도록 지정해준다.
 * 4. 그렇게 구조체를 초기화 했다면 kevent함수를 호출해서, 서버 소켓에 대한 이벤트를 감지하도록 해준다. 이렇게 하면 에코서버가 시작되는 것이다.
 * 5. 이제 메인 루프를 돈다 while (1)
 * 6. new_events = kevent(kq, &change_list[0], change_list.size(), event_list, 8, NULL);
 *  6-1. 현재 kqueue 안에 있는 감지할 이벤트를 쭉 탐색해서 변화가 생긴 이벤트를 change_list 배열에 넣어주게 됩니다. timeout을 설정X
 *  6-2. 여기서는 event_list를 8로 했는데 8개 이상이 들어오는 경우 다음 kevent 호출 때 들어가게 됩니다.
 *  6-3. 이벤트가 발생한 갯수가 new_event 변수에 들어가게 됩니다.
 * 7. 이후 이벤트가 발생한 소켓에 땨라서 각각 처리를 진행해줍니다.
 * 7-1. Read 이벤트가 발생한 경우
 *  7-1-1. 서버 소켓인 경우 : 새로운 클라이언트 소켓을 생성하고 그것을 이벤트에 read,write 등록해줍니다.
 *  7-1-2. 클라이언트 소켓인 경우 : 클라이언트가 보내는 데이터를 읽어서, 데이터 저장소에 붙혀줍니다.
 * 7-2 Write 이벤트가 발생한 경우
 *  7-2-1 클라이언트 소켓에서만 write이벤트가 발생합니다.
 *  7-2-2.클라이언트 소켓에 쌓여있는 데이터들을 write 해줍니다.
 * @note kqueue에 한번 등록한 이벤트는 삭제하지 않는한 계속 존재한다는 사실을 기억합시다.
 */
class Kserver{
	public :


		explicit Kserver(char *port);
		~Kserver();
		void  serverInit();
		// void  sockAccept();//현재 사용하지 않습니다.
		void  startWorking();
	private:
		Kserver();
		void  sockInit();
		void  sockBind();
		void  sockListen();
		void  handleEvents();
		void  registerNewClnt();
		void  sockReadable(struct kevent *cur_event);
		void  sockWriterable(struct kevent *cur_event);
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
		//클라언트의 소켓 번호와 보내는 데이터를 담는 변수
		std::map<int, std::string> clnt_store_;
};

#endif
