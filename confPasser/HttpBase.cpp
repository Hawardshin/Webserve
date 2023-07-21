# include "HttpBase.hpp"


HttpBase::HttpBase() :  root_(""), autoindex_(false), client_max_body_size_(-1), error_page_(""){
	directives_[0] = "root";
	directives_[1] = "index";
	directives_[2] = "autoindex";
	directives_[3] = "client_max_body_size";
	directives_[4] = "error_page";
}
HttpBase:: ~HttpBase(){}

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

