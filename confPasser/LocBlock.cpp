#include "LocBlock.hpp"

LocBlock::LocBlock() : root_(false), index_(false), autoindex_(false),error_page_(false){}
LocBlock::~LocBlock(){}
std::map<std::string, std::string>& LocBlock::getDirStore(){
	return (loc_directives_);
}
