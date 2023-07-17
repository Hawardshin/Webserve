#ifndef HTTPBLOCK_HPP
# define HTTPBLOCK_HPP
#include "ServBlock.hpp"
/**
 * @brief HTTP block의 정보를 담고있는 블록. 내부에 서버 블록들을 가지고 있다.
 * @details [서버 네임이 둘 이상 일치하는 경우 우선순위]
		1. 정확한 이름
		2. 별표로 시작하는 가장 긴 와일드카드 이름(예: "*.example.org")
		3. 별표로 끝나는 가장 긴 와일드카드 이름(예: "mail.*")
 * @details [와일드 카드]
		- 와일드 카드 규칙 : 와일드 카드는 반드시 시작과 끝에만 붙일 수 있습니다.
		- 스페셜 와일드 카드 (`.example.org`) : 이 와일드 카드는 `example.org` 로 정확한 서버이름을 정하기도 하고 `*.example.org` 를 의미하기도 합니다.
 * @details [서버 블록 찾기 규칙]
		1. 포트 번호를 기준으로 쭉 탐색한다.
		2. 같은 포트번호가 있다면 그 포트번호에 해당하는 서버들을 본다.
		3. 그리고 서버네임을 확인해서 해당하는 서버네임 으로 호스팅 해준다.
			a. `nginx`는 먼저 서버 블록의 `listen 지시어`에 대해 `요청의 IP 주소와 포트를 테스트`합니다.
			b. 그런 다음 요청의 `"호스트" 헤더 필드`를 `IP 주소` 및 `포트와 일치하는 서버 블록`의 `server_name` 항목과 비교하여 테스트합니다.
			c. 서버 이름을 찾을 수 없는 경우 요청은 `기본 서버`에서 처리됩니다.
 *
 */
class HttpBlock{
public:
	HttpBlock();
	~HttpBlock();
	ServBlock findServBlock(std::string serv_name);//http메세지에서 host_name을 인자로 줍니다.
	std::map<std::string, std::string>& getDirStore();
	void	makeBlock(std::string line, std::ifstream& input, int& line_len_);
private:
	void	makeServerBlock(std::ifstream& input, int& line_len_);
	void	makeOtherBlock(std::ifstream& input, int& line_lne_);
	std::vector<ServBlock> serv_store_;
	std::vector<OtherBlock> other_store_;
	std::map<std::string, std::string> http_directives_;
	// bool root_;
	// bool index_;
	// bool autoindex_;
	// bool error_page_;
};

#endif
