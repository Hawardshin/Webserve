#include "LocBlock.hpp"

LocBlock::LocBlock() : root_(false), index_(false), autoindex_(false),error_page_(false){}
LocBlock::~LocBlock(){}
std::map<std::string, std::string>& LocBlock::getDirStore(){
	return (loc_directives_);
}

void	LocBlock::makeBlock(std::string line, std::ifstream& input, int& line_len_){
	std::cerr<< line << " : " <<line_len_;
	(void) input;
	throw(std::runtime_error("CAN't Make block in Loc block!"));
}
