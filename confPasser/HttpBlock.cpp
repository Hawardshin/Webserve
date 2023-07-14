# include "HttpBlock.hpp"
HttpBlock::HttpBlock(){}
	// explicit HttpBlock();
HttpBlock::~HttpBlock(){}

//http메세지에서 host_name을 인자로 줍니다.
ServBlock HttpBlock::findServBlock(std::string serv_name){
	(void) serv_name;
	return serv_store_[0];
}
