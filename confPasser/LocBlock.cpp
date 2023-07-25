#include "LocBlock.hpp"


LocBlock::LocBlock(std::string loc_info) : rank_(0), upload_store_(""), loc_info_(loc_info), return_code_(-1), return_path_(""), is_limit_except_(false), cgi_pass_(""), combined_path_(""){}

LocBlock::~LocBlock(){}
// LocBlock& LocBlock::operator=(const LocBlock& obj){
// 	root_ = obj.root_;
// 	index_ = obj.index_;
// 	autoindex_ = obj.autoindex_;
// 	client_max_body_size_ = obj.client_max_body_size_;
// 	error_code_ = obj.error_code_;
// 	error_page_ = obj.error_page_;

// 	loc_directives_ = obj.loc_directives_;
// 	upload_store_ = obj.upload_store_;
// 	loc_info_ = obj.loc_info_;
// 	return_code_ = obj.return_code_;
// 	return_path_ = obj.return_path_;
// 	is_limit_except_ = obj.is_limit_except_;
// 	cgi_pass_ = obj.cgi_pass_;
// 	deny_methods_ = obj.deny_methods_;
// 	combined_path_ = obj.combined_path_;
// 	return (*this);
// }


/**
 * @brief loc_directives_ 반환
 *
 * @note 템플릿 사용 위해서 반드시 필요
 * @return std::map<std::string, std::string>& 인자로 받아서 변경시키기 위해서 레퍼런스 타입으로 반환함
 */
std::map<std::string, std::string>& LocBlock::getDirStore(){return (loc_directives_);}

const std::string& LocBlock::getUploadStore(){return upload_store_; }
const std::string& LocBlock::getLocInfo(){return loc_info_;}
const int& LocBlock::getReturnCode(){return return_code_;}
const std::string& LocBlock::getReturnPath(){return return_path_;}
const bool& LocBlock::isLimit(){return is_limit_except_;}
const std::string& LocBlock::getCgiPath(){return cgi_pass_;}
const std::vector<std::string>& LocBlock::getDenyMethod(){return deny_methods_;}
const int& LocBlock::getRank() const {return rank_;}

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
	is_limit_except_ = true;
	splitAndStore(deny_methods_,line.substr(12, line.find('{') - 12) ,' ');
	for (std::vector<std::string>::iterator it = deny_methods_.begin(); it != deny_methods_.end(); it++){
		if (checkMethodName(*it) == OTHER_METHOD)
			throw(std::runtime_error("THIS IS NOT ALLOW METHOD!"));
	}
	while (getline(input, line)){
		trimComment(line);
		trimSidesSpace(line);
		if (line == "")
			continue;
		if (line == "}")
			return;
		line = line.substr(0, line.find(';'));
		line_len_++;
		splitKeyVal(key, value, line);
		if (key != "deny" ||  value != "all")
			throw(std::runtime_error("ERROR it must only deny all"));
	}
	throw(std::runtime_error("Not closed by }"));
}

/**
 * @brief location block의 모든 directive를 정제하는 함수
 *
 */
void	LocBlock::refineAll(){
	parseHttpDirective(loc_directives_);
	parseLocDirective();
	if (loc_info_ == "/")
		return ;
	for (size_t i = 0;i < loc_info_.size(); i++){
		if (loc_info_[i] == '/')
			rank_++;
	}
}


void	LocBlock::printInfo(){
	printHttpInfo();
	std::cout << "\n---------------[Location]------------------\n";
	std::cout << "rank_:|" << rank_ << "|\n";
	std::cout << "upload_store_:|" << upload_store_ << "|\n";
	std::cout << "loc_info_:|" << loc_info_ << "|\n";
	std::cout << "return_code_:|" << return_code_ << "|\n";
	std::cout << "return_path_:|" << return_path_ << "|\n";
	std::cout << "is_limit_except_:|" << is_limit_except_ << "|\n";
	std::cout << "cgi_pass_:|" << cgi_pass_ << "|\n";
	std::cout << "[deny_methods_]\n";
	for (size_t i = 0;i < deny_methods_.size(); i++){
			std::cout << "deny_methods_[" << i << "]:|" << deny_methods_[i] << "|\n";
	}
	std::cout << "combined_path_:|" << combined_path_ << "|\n";
}



void	LocBlock::setConbinePath(std::string conbine_path){combined_path_ = conbine_path;}

/* private */
LocBlock::LocBlock(){}

/**
 * @brief location 블록에만 해당하는 값들을 정제
 *
 */
void	LocBlock::parseLocDirective(){
	std::map<std::string, std::string>::iterator it = loc_directives_.find("upload_store");
	if (it != loc_directives_.end())
		upload_store_ = (*it).second;
	it = loc_directives_.find("return");
	if (it != loc_directives_.end())
		parseReturn((*it).second);
	it = loc_directives_.find("cgi_pass");
	if (it != loc_directives_.end())
		cgi_pass_ = (*it).second;
}

/**
 * @brief return에 해당하는 부분을 파싱 (redirection과 연관있습니다.)
 *
 * @param ret_line return key를 가진 directive의 value 값 입니다.(map["return"];)
 */
void	LocBlock::parseReturn(std::string ret_line){
	std::vector<std::string> tmp;
	splitAndStore(tmp, ret_line, ' ');
	if (tmp.size() != 2)
		throw(std::runtime_error("you must return argument only two!"));
	return_code_ = stringToInt(tmp[0]);
	return_path_ = tmp[1];
}

bool cmp(const LocBlock& a, const LocBlock& b){
	return (a.getRank() > b.getRank());
}
