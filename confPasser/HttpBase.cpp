# include "HttpBase.hpp"


HttpBase::HttpBase() :  root_(""), autoindex_(false), client_max_body_size_(-1), error_page_(""){}
HttpBase:: ~HttpBase(){}
const std::string& HttpBase::getRoot(){return root_;}
const std::vector<std::string>& HttpBase::getIndex(){return index_;}
const bool& HttpBase::isAutoIndex(){return autoindex_;}
const int& HttpBase::clientMaxBodySize(){return client_max_body_size_;}
const std::vector<int>& HttpBase::getErrorCode(){return error_code_;}
const std::string& HttpBase::getErrorPage(){return error_page_;}


void	HttpBase::printHttpInfo(){
	std::cout << "\n---------------[http]------------------\n";
	std::cout << "root:|" << root_ << "|\n";
	std::cout << "[index]\n";
	for (size_t i = 0;i < index_.size(); i++){
		std::cout << "index[" << i << "]:|" << index_[i] << "|\n";
	}
	std::cout << "autoindex:|" << autoindex_ << "|\n";
	std::cout << "client_max_size:|" << client_max_body_size_ << "|\n";
	std::cout << "[error_code]\n";
	for (size_t i = 0;i < error_code_.size(); i++){
		std::cout << "error_code_[" << i << "]:|" << error_code_[i] << "|\n";
	}
	std::cout << "error_page:|" << error_page_ << "|\n";
}


/**
 * @brief map에 이미 다 들어있는데 그 값을 사용할 수 있게 정제해준다.
 *
 * @param dir_store 해당하는 map값
 */
void	HttpBase::parseHttpDirective(std::map<std::string, std::string>& dir_store){
	if (dir_store.find("root") != dir_store.end())
		root_ = dir_store["root"];
	if (dir_store.find("index") != dir_store.end())
		splitAndStore(index_,dir_store["index"],' ');
	if (dir_store.find("autoindex") != dir_store.end())
		setAutoIndex(dir_store["autoindex"]);
	if (dir_store.find("client_max_body_size") != dir_store.end())
		client_max_body_size_ = stringToInt(dir_store["client_max_body_size"]);
	if (dir_store.find("error_page") != dir_store.end())
		 setErrorPage(dir_store["error_page"]);
}

/**
 * @brief Autoindex를 설정합니다.
 *
 * @param value key value로 잘린 map에서 value값
 */
void	HttpBase::setAutoIndex(const std::string& value){
	if (value == "on")
			autoindex_ = true;
	else if (value == "off")
		autoindex_ = false;
	else
		throw(std::invalid_argument("ERROR in AUTO index\n"));
}

/**
 * @brief 에러페이지를 설정합니다.
 *
 * @param line 에러페이지의 status 코드와 경로가 있는 헌쥴울 전달해준다.
 */
void	HttpBase::setErrorPage(const std::string& line){
	//거꾸로 탐색합니다. 뒷쪽에 에러페이지는 하나만 에러코드는 여러개 올 수 있습니다.
	int i;
	for (i = line.size() - 1;i  > 0; i--){
		if (line[i] == ' ')
			break;
	}
	if (i == 0)
		throw(std::runtime_error("ERROR_PAGE SETING ERROR!!"));
	// root_ = line.substr(i + 1);
	splitAndStore(error_code_,  line.substr(0, i), ' ');
	error_page_ = line.substr(i+1);
}
