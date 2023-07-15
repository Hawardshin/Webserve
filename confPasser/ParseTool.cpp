# include "ParseTool.hpp"
# include "OtherBlock.hpp"
/**
 * @brief 들어온 문자열의 양옆에 있는 space와 tab을 지워주는 함수
 *
 * @param line 변경할 문자열
 */
void	trimSidesSpace(std::string &line){
	size_t i;
	//앞쪽에 스페이스 지운다.
	for (i = 0; i < line.size();	i++){
		if (line[i] != '\t' && line[i] != ' ')
			break;
	}
	line.erase(0, i);
	// std::cout << "line:|"<< line << "|\n";
	//뒤쪽의 스페이스와 tab 을 다 지운다.
	for (i = line.size() - 1; i > 0; i--){
		if (line[i] != '\t' && line[i] != ' ')
				break ;
	}
	line.erase(line.begin() + i + 1, line.end());
}

/**
 * @brief #으로 시작하는 comment를 전부 지워준다.
 *
 * @param line 변경할 문자열
 */
void	trimComment(std::string &line){
	size_t tmpos = line.find('#');
	if (tmpos != std::string::npos){
		line.erase(tmpos,line.size());
		line = line.substr(0, tmpos);
	}
}


void	splitKeyVal(std::string& key, std::string &value, std::string &line){
		//스페이스를 기준으로 key와 value를 만든다음에 그값을 map에 넣어준다.
	size_t tmpos = line.find(' ');
	//directive를 잘랐는데 directive<space>value로 되어있어야 하기 때문에 아닌 경우에 대해서 처리해준 것입니다.
	if (tmpos == std::string::npos)
		throw(std::runtime_error("ERROR DIRECTIVE key"));
	key = line.substr(0,tmpos);
	std::cout << "key:|"<< key << "|" << std::endl;
	for (; tmpos < line.size(); tmpos++){
		if (line[tmpos] != ' ' && line[tmpos] != '\t')
			break ;
	}
	value = line.substr(tmpos);
	std::cout << "value:|"<< value << "|" << std::endl;
}

/**
 * @brief 어떤 블록인지 리턴해주는 함수
 *
 * @details switch 문 쓰려고 만들었어요
 * @param block_name 블록 이름
 * @return e_block ENUM 값으로 리턴해준다.
 */
e_block	check_blockname(std::string block_name){
	if (block_name == "http")
		return (HTTP);
	if (block_name == "server")
		return (SERVER);
	if (block_name == "location")
		return (LOCATION);
	return (OTHER);
}
