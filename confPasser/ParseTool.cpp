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
	std::cout << "line:|"<< line << "|\n";
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
