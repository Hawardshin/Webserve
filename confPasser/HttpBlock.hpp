#ifndef HTTPBLOCK_HPP
# define HTTPBLOCK_HPP
#include "ServBlock.hpp"
class HttpBlock{
public:
	HttpBlock();
	// explicit HttpBlock();
	~HttpBlock();
	ServBlock findServBlock(std::string serv_name);//http메세지에서 host_name을 인자로 줍니다.
private:
	std::vector<ServBlock> serv_store_;
	std::vector<OtherBlock> other_store_;
	std::map<std::string, std::string> http_directives_;
	std::string root_;
	std::string index_;
	std::string autoindex_;
	std::string error_page_;
};

#endif
