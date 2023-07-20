#include "LocBlock.hpp"


LocBlock::LocBlock(std::string loc_info) : upload_store_(""), loc_info_(loc_info), return_code_(-1), return_string_(""), is_limit_except_(false), cgi_pass_(""){}

LocBlock::~LocBlock(){}

/**
 * @brief loc_directives_ 반환
 *
 * @note 템플릿 사용 위해서 반드시 필요
 * @return std::map<std::string, std::string>& 인자로 받아서 변경시키기 위해서 레퍼런스 타입으로 반환함
 */
std::map<std::string, std::string>& LocBlock::getDirStore(){
	return (loc_directives_);
}

/**
 * @brief location block에서는 limit_except 블록만 올 수 있습니다.
 *
 * @param line 반드시 "limit_except GET POST HEAD {" 이런 느낌으로 옵니다.
 * @param input 열어둔 파일시스템
 * @param line_len_ conf파일 현재까지 읽은 길이
 *
 * @warning limit_except 에 올 수 있는 메서드는 임의롤 줄였습니다.
 * 추가적으로 deny all이외에 다른 인자는 받지 않습니다.
 */
void	LocBlock::makeBlock(std::string line, std::ifstream& input, int& line_len_){
	std::string key,value;
	if (line.find("limit_except") == std::string::npos)
		throw(std::runtime_error("CAN't Make block in Loc block!(only allow limit_except)"));
	splitAndStore(deny_methods_, line.substr(12), ' ');
	for (std::vector<std::string>::iterator it = deny_methods_.begin(); it != deny_methods_.end(); it++){
		std::cout <<"-----------------" <<*it << "\n";
		if (checkMethodName(*it) == OTHER_METHOD)
			throw(std::runtime_error("THIS IS NOT ALLOW METHOD!"));
	}
	while (getline(input, line)){
		trimComment(line);
		trimSidesSpace(line);
		line = line.substr(0, line.find(';'));
		line_len_++;
		if (line == "")
			continue;
		if (line == "}")
			break;
		splitKeyVal(key, value, line);
		if (key != "deny" ||  value != "all")
			throw(std::runtime_error("ERROR it must only deny all"));
	}
}
//this is cpp 11 for test.. I will delete it
void	LocBlock::printAllBlock(){
	std::cout << "LocBlock name is :|" <<loc_info_ << "\n";
	for (auto it: loc_directives_){
		std::cout <<"key:|" << it.first<< "|value:|" <<it.second << "|\n";
	}
}


/* private */
LocBlock::LocBlock(){}
