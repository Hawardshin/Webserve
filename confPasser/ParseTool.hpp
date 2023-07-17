#ifndef PARSETOOL_HPP
# define PARSETOOL_HPP
# include <fstream>
# include <sstream>
# include <iostream>
# include <string>
# include <vector>
# include <map>
# include <algorithm>
# include <cmath>
typedef enum blocktype{
		HTTP,
		SERVER,
		LOCATION,
		OTHER
}e_block;

void	trimSidesSpace(std::string &line);
void	trimComment(std::string &line);
void	splitKeyVal(std::string& key, std::string &value, std::string &line);
void  extractDirective(std::string line, std::map<std::string, std::string>& directives_map);
e_block	check_blockname(std::string block_name);


/**
 * @brief 재귀적으로 괄호가 닫힐때까지 탐색하는 함수
 * 탬플릿으로 블록을 받고 각 블록 내부의 함수를 활용해서 재귀적으로 타고 갑니다.
 *
 * @tparam T (HttpBlock, ServBlock, OtherBlock, locBlock) 클래스가 들어옵니다.
 * @warning 호출 하기 전에 T block 안에 makeBlock() 함수가 있는지 확인합니다.
 * @param input conf파일을 열어 놓은 ifstream 입니다.
 * @param line_len_ ConfPaser에서 있는 멤버변수입니다. 에러가 어디서 났는지 알기위해 계속 가져갑니다.
 * @param block 새로 만든 즉 벡터에 들어갈 블록이 들어옵니다.
 */
template <typename T>
void	parseUntilEnd(std::ifstream& input, int& line_len_, T& block){
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
		if (dir_pos_c != std::string::npos ){  //괄호가 닫히는 경우 재귀 종료
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

void  checkOverFlow(double d);
void	splitBySpace(std::vector<std::string>& store, std::string line, char delimiter);
void	splitBySpace(std::vector<int>& store, std::string line, char delimiter);

#endif
