#ifndef CONFPARSER_HPP
# define CONFPARSER_HPP
# include "HttpBlock.hpp"
# include "IBlock.hpp"
/**
 * @brief 루트에 해당하는 클래스라고 보면 됩니다.
 * @details 사용할 지시어가 올바른 위치에 있지 않는 것에 대한 에러는 처리하지 않습니다.
 * @note  모든 블록 클래스는 makeBlock과 getDirStore 함수를 가지고 있습니다.
 * 템플릿으로 재귀적으로 처리하기 위해서.
 */
class ConfParser : public IBlock{
public:

	ConfParser();//default_conf_file
	~ConfParser();

	std::map<std::string, std::string>& getDirStore();
	void	confPathInit(char* path);
	void	confInit();
	void	makeBlock(std::string line, std::ifstream& input, int& line_len);
	void	printAllBlock();//testFunction It will Delete
private:
	void	makeHttpBlock(std::ifstream& input);
	void	makeOtherBlock(std::ifstream& input);
	std::string	file_name_;
	int	line_len_;
	std::vector<HttpBlock>	http_store_;
	std::vector<OtherBlock>	other_store_;
	std::map<std::string, std::string>	root_directives_;//key : derective, value : value

};

#endif
