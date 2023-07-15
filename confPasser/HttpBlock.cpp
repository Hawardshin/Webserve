# include "HttpBlock.hpp"
HttpBlock::HttpBlock() : root_(false), index_(false), autoindex_(false), error_page_(false){}

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

void	HttpBlock::parseUntilEnd(std::ifstream& input,int &line_len_){
	std::string line;
	std::string directive = "";
	while (std::getline(input, line)){
		trimComment(line);
		trimSidesSpace(line);
		line_len_++;
		if (line == "")
			continue;
		size_t dir_pos_a = line.find('{');
		size_t dir_pos_b = line.find(';');
		// size_t dir_pos_c = line.find('}');
		std::cout << "2. line|"<< line << "|" << std::endl;
		if ((dir_pos_a == std::string::npos && dir_pos_b == std::string::npos)  || \
					(dir_pos_a != std::string::npos && dir_pos_b != std::string::npos))
			throw(std::runtime_error(" [ERROR in Nginx conf_file]"));
		// else if (dir_pos_b != std::string::npos && dir_pos_a == std::string::npos)
		// 		// extractDirective(line.substr(0, dir_pos_b));
		// else // {가 나오는 경우
		// 	makeBlock(line, input);
	}
}
