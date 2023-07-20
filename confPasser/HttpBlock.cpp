# include "HttpBlock.hpp"
HttpBlock::HttpBlock() : root_(""), autoindex_(false), client_max_body_size_(-1), error_page_(""){}
HttpBlock::~HttpBlock(){}

/**
 * @brief 서버이름 즉 http의 host_name을 기준으로 해당하는 서버를 찾는 함수

 * @param serv_name http메세지에서 host_name
 * @return ServBlock 해당하는 서버 블록 또는 default 서버는 port 번호가 같으면 그걸로 가는것 입니다.(포트가 다르면 짤.)
 */
ServBlock HttpBlock::findServBlock(std::string serv_name){
	(void) serv_name;
	return (serv_store_[0]);
}

/**
 * @brief http_directives_ 반환
 *
 * @note 템플릿 사용 위해서 반드시 필요
 * @return std::map<std::string, std::string>& 인자로 받아서 변경시키기 위해서 레퍼런스 타입으로 반환함
 */
std::map<std::string, std::string>& HttpBlock:: getDirStore(){
	return (http_directives_);
}

/**
 * @brief 블록을 만드는 함수 서버 블록과 otherBlock허용
 *
 * @param line 파싱중인 한줄 라인(주석과 스페이스를 삭제한)
 * @param input 파싱중인 설정파일
 * @param line_len_ 설정파일을 어디까지 읽었는지 확인
 * @note 템플릿 사용을 위해 반드시 필요
 * @warning  http, location 블록은 에러로 감지함
 */
void	HttpBlock::makeBlock(std::string line, std::ifstream& input, int& line_len_){
	size_t pos = line.find('{');
	std::string block_name = line.substr(0, pos);
	trimSidesSpace(block_name);
	// std::cout << "5. |" << block_name << "|"<< std::endl;
	if (pos != line.size() - 1 || block_name == "")
		throw(std::runtime_error("this is not block"));
	switch(checkBlockName(block_name)){
		case HTTP :throw(std::runtime_error("this is not GOOD HTTP block"));
		case SERVER : makeServerBlock(input, line_len_);
			break;
		case LOCATION : throw(std::runtime_error("this is not LOC block"));
		case OTHERBLOCK : makeOtherBlock(input, line_len_);
			break;
	}
}

void	HttpBlock::printAllBlock(){
	std::cout << "------------------IN HTTPBLOCK Directives!!\n";
	for (auto it : http_directives_){
		std::cout <<"key:|" << it.first<< "|value:|" <<it.second << "|\n";
	}

	for (auto it : serv_store_){
		std::cout << "----------------Serv BLOCK INTO\n";
		it.printAllBlock();
	}
}


/**
 * @brief 서버블록을 만드는 함수
 *
 * @param input 열어둔 설정파일
 * @param line_len_ 설정파일 읽은 길이
 * @note 재귀적으로 돌기 위한 템플릿 함수 parseUntilEnd를 호출한다.
 */
void	HttpBlock::makeServerBlock(std::ifstream& input, int& line_len_){
	ServBlock new_block;
	serv_store_.push_back(new_block);
	parseUntilEnd(input, line_len_, serv_store_[serv_store_.size() - 1]);
}

/**
 * @brief Other 블록을 만드는 함수
 *
 * @param input 열어둔 설정파일
 * @param line_len_ 설정파일 읽은 길이
 * @note 재귀적으로 돌기 위한 템플릿 함수 parseUntilEnd를 호출한다.
 */
void	HttpBlock::makeOtherBlock(std::ifstream& input, int& line_len_){
	OtherBlock new_block;
	other_store_.push_back(new_block);
	parseUntilEnd(input, line_len_, other_store_[other_store_.size() - 1]);
}
