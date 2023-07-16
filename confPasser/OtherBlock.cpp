# include "OtherBlock.hpp"

// void	OtherBlock::parseUntilEnd(std::ifstream& input){
// 	(void)input;
// }

// void	makeBlock(std::string line, std::ifstream& input){}

std::map<std::string, std::string>& OtherBlock::getDirStore(){
	return (other_directives_);
}
