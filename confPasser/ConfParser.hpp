#ifndef CONFPARSER_HPP
# define CONFPARSER_HPP
# include "HttpBlock.hpp"


class ConfParser{
public:
	ConfParser();//default_conf_file

	~ConfParser();

	void  confPathInit(char* argv);
	void  confInit();//여기서 HTTP 블록 벡터를 다 채웁니다.(http안에서 serv_block, serv_block안에 loc_block까지 다 채우기)
private:
	void  parseConf(std::ifstream& input);
	void  extractDirective(std::string line);
	void  deleteComment(std::string& line);
	std::string file_name_;
	std::vector<HttpBlock> http_store_;
	std::vector<OtherBlock> other_store_;
	std::map<std::string, std::string> root_directives_;
	//key : derective value : value

	std::string root_;
	std::string index_;
	std::string autoindex_;
	std::string error_page_;
};

#endif
