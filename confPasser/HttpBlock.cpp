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

std::map<std::string, std::string>& HttpBlock:: getDirStore(){
	return (http_directives_);
}

void	HttpBlock::makeBlock(std::string line, std::ifstream& input, int& line_len_){
	size_t pos = line.find('{');
	std::string block_name = line.substr(0, pos);
	trimSidesSpace(block_name);
	std::cout << "5. |" << block_name << "|"<< std::endl;
	if (pos != line.size() - 1 || block_name == "")
		throw(std::runtime_error("this is not block"));
	switch(check_blockname(block_name)){
		case HTTP :throw(std::runtime_error("this is not GOOD HTTP block"));
		case SERVER : makeServerBlock(input, line_len_);
			break;
		case LOCATION : throw(std::runtime_error("this is not LOC block"));
		case OTHER : makeOtherBlock(input, line_len_);
			break;
	}
}

void	HttpBlock::makeServerBlock(std::ifstream& input, int& line_len_){
	ServBlock new_block;
	serv_store_.push_back(new_block);
	// (void)input;
	// (void) line_len_;
	parseUntilEnd(input, line_len_, new_block);
}

void	HttpBlock::makeOtherBlock(std::ifstream& input, int& line_len_){
	OtherBlock new_block;
	other_store_.push_back(new_block);
	parseUntilEnd(input, line_len_, new_block);
}
