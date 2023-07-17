#include "LocBlock.hpp"


LocBlock::LocBlock(std::string loc_info) :root_(""), autoindex_(false), client_max_body_size_(-1), error_page_(""), upload_store_(""), loc_info_(loc_info), return_code_(-1), return_string_(""), is_limit_except_(false), cgi_pass_(""){}
LocBlock::~LocBlock(){}
std::map<std::string, std::string>& LocBlock::getDirStore(){
	return (loc_directives_);
}

void	LocBlock::makeBlock(std::string line, std::ifstream& input, int& line_len_){
	std::cerr<< line << " : " <<line_len_;
	(void) input;
	throw(std::runtime_error("CAN't Make block in Loc block!"));
}

/* private */
LocBlock::LocBlock(){}
