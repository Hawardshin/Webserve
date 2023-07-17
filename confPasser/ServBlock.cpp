#include "ServBlock.hpp"
/**
 * @brief Construct a new Serv Block:: Serv Block object
 * default listen은 8000번으로 했습니다.
 *
 */
// ServBlock::ServBlock() : root_(false), index_(false), autoindex_(false), error_page_(false),server_name_(""), listen_(8000),default_server_(false) {}
ServBlock::ServBlock() {}
ServBlock::~ServBlock(){

}

std::map<std::string, std::string>& ServBlock::getDirStore(){
	return (serv_directives_);
}

/**
 * @brief 전달된 경로에 대해서 어떤 규칙을 따라야 하는지 리턴해주는 함수입니다.
 *
 * @param http에서 path를 추출해서 원하는 블럭을 얻을 때 사용합니다.
 * @return LocBlock 전딜힌 path에 대해서 해당하는 location block을 리턴해줍니다.
 */
LocBlock ServBlock::findLocBlock(std::string path){
	(void)path;
	return loc_store_[0];
}

void	ServBlock::makeBlock(std::string line, std::ifstream& input, int& line_len_){
	size_t pos = line.find('{');
	std::string block_name = line.substr(0, pos);
	trimSidesSpace(block_name);
	std::cout << "5. |" << block_name << "|"<< std::endl;
	if (pos != line.size() - 1 || block_name == "")
		throw(std::runtime_error("this is not block"));
	switch(check_blockname(block_name)){
		case HTTP :throw(std::runtime_error("this is not GOOD HTTP block"));
		case SERVER : throw(std::runtime_error("this is not GOOD SERVER block"));
		case LOCATION : makeLocBlock(input, line_len_, block_name);
			break;
		case OTHER : makeOtherBlock(input, line_len_);
			break;
	}
}

void	ServBlock::makeLocBlock(std::ifstream& input, int& line_len_, std::string& block_name){
	// std::cout << "---Loc blk name : |" << block_name << "|\n";
	// std::cout << block_name.find("location") << "\n";
	if (block_name == "location")
		throw(std::runtime_error("location block Don't have pathinfo"));
	std::string loc_info =  block_name.substr(8);
	trimSidesSpace(loc_info);
	// std::cout << "|"<< loc_info << "|\n";
	LocBlock new_block(loc_info);
	loc_store_.push_back(new_block);
	parseUntilEnd(input, line_len_, new_block);
}

void	ServBlock::makeOtherBlock(std::ifstream& input, int& line_len_){
	OtherBlock new_block;
	other_store_.push_back(new_block);
	parseUntilEnd(input, line_len_, new_block);
}
