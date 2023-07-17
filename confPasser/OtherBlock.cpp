# include "OtherBlock.hpp"

// void	OtherBlock::parseUntilEnd(std::ifstream& input){
// 	(void)input;
// }

// void	makeBlock(std::string line, std::ifstream& input, int& line_len_){}

std::map<std::string, std::string>& OtherBlock::getDirStore(){
	return (other_directives_);
}

void	OtherBlock::makeBlock(std::string line, std::ifstream& input, int& line_len_){
	size_t pos = line.find('{');
	std::string block_name = line.substr(0, pos);
	trimSidesSpace(block_name);
	std::cout << "5. |" << block_name << "|"<< std::endl;
	if (pos != line.size() - 1 || block_name == "")
		throw(std::runtime_error("this is not block"));
	switch(checkBlockName(block_name)){
		case HTTP :throw(std::runtime_error("this is not GOOD HTTP block"));
		case SERVER : throw(std::runtime_error("HERE IS OTHERBLOCK!"));
			break;
		case LOCATION : throw(std::runtime_error("this is not LOC block"));
		case OTHERBLOCK : makeOtherBlock(input, line_len_);
			break;
	}
}

void	OtherBlock::makeOtherBlock(std::ifstream& input,int& line_len_){
	OtherBlock new_block;
	other_store_.push_back(new_block);
	parseUntilEnd(input, line_len_, new_block);
}
