#ifndef PARSETOOL_HPP
# define PARSETOOL_HPP
# include <fstream>
# include <sstream>
# include <iostream>
# include <string>
# include <vector>
# include <map>
# include <algorithm>


typedef enum blocktype{
		HTTP,
		SERVER,
		LOCATION,
		OTHER,
}e_block;

void	trimSidesSpace(std::string &line);
void	trimComment(std::string &line);
void	splitKeyVal(std::string& key, std::string &value, std::string &line);
void  extractDirective(std::string line, std::map<std::string, std::string>& directives_map);
e_block	check_blockname(std::string block_name);

template <typename T>
void	parseUntilEnd(std::ifstream& input,int& line_len_, T& block){
	std::string line;

	while (std::getline(input, line)){
		trimComment(line);
		trimSidesSpace(line);
		line_len_++;
		if (line == "")
			continue;
		size_t dir_pos_a = line.find('{');
		size_t dir_pos_b = line.find(';');
		size_t dir_pos_c = line.find('}');
		std::cout << "2. line|"<< line << "|" << std::endl;
		if (dir_pos_c != std::string::npos ){  //괄호가 닫히는 경우
			if (line.size() != 1)
				throw(std::runtime_error(" '{' is only line by line"));
			return ;
		}
		else if ((dir_pos_a == std::string::npos && dir_pos_b == std::string::npos)  || \
					(dir_pos_a != std::string::npos && dir_pos_b != std::string::npos))
			throw(std::runtime_error(" [ERROR in Nginx conf_file]"));
		else if (dir_pos_b != std::string::npos && dir_pos_a == std::string::npos)
				extractDirective(line.substr(0, dir_pos_b), block.getDirStore());
		else // {가 나오는 경우
			block.makeBlock(line, input, line_len_);
	}
	throw(std::runtime_error("NOT CLOSE the {}"));
}

#endif
