# include "HttpBase.hpp"


HttpBase::HttpBase() :  root_(""), autoindex_(false), client_max_body_size_(-1), error_page_(""){}
HttpBase:: ~HttpBase(){}
void	HttpBase::parseHttpDirective(const std::pair<std::string, std::string> &direc){
	switch (checkDirective(direc.first)){
		case ROOT : root_ = direc.second;
			break ;
		case INDEX : splitAndStore(index_,direc.second,' ');
			break ;
		case AUTOINDEX : setAutoIndex(direc.second);
			break;
		case CLINET_MAX_BODY_SIZE : client_max_body_size_ = stringToInt(direc.second);
			break;
		case ERROR_PAGE : setErrorPage(direc.second);
			break;
	}
}

void	HttpBase::setAutoIndex(const std::string& value){
	if (value == "on")
			autoindex_ = true;
	else if (value == "off")
		autoindex_ = false;
	else
		throw(std::invalid_argument("ERROR in AUTO index\n"));
}

void	HttpBase::setErrorPage(const std::string& line){
	int i;
	for (i = line.size() - 1;i  > 0; i--){
		if (line[i] == ' ')
			break;
	}
	if (i == 0)
		throw(std::runtime_error("ERROR_PAGE SETING ERROR!!"));
	root_ = line.substr(i + 1);
	splitAndStore(error_code_, line.substr(0, i), ' ');
}

