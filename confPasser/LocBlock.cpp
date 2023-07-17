#include "LocBlock.hpp"


LocBlock::LocBlock(std::string loc_info) :root_(""), autoindex_(false), client_max_body_size_(-1), error_page_(""), upload_store_(""), loc_info_(loc_info), return_code_(-1), return_string_(""), is_limit_except_(false), cgi_pass_(""){}
LocBlock::~LocBlock(){}
std::map<std::string, std::string>& LocBlock::getDirStore(){
	return (loc_directives_);
}

void	LocBlock::makeBlock(std::string line, std::ifstream& input, int& line_len_){
	if (line.find("limit_except") == std::string::npos)
		throw(std::runtime_error("CAN't Make block in Loc block!(only allow limit_except)"));
	// std::cout << "|"<< line <<"|" <<line.substr(12) << "|\n";
	splitBySpace(deny_methods_, line.substr(12), ' ');
	// while (getline())
}

/* private */
LocBlock::LocBlock(){}
