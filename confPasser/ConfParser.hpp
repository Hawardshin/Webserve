#ifndef CONFPARSER_HPP
# define CONFPARSER_HPP
# include "HttpBlock.hpp"


class ConfParser{
public:

	ConfParser();//default_conf_file
	~ConfParser();

	std::map<std::string, std::string>& getDirStore();
	void	confPathInit(char* argv);
	void	confInit();
	void	makeBlock(std::string line, std::ifstream& input);

private:
	void	parseConf(std::ifstream& input);
	void	makeHttpBlock(std::ifstream& input);
	void	makeOtherBlock(std::ifstream& input);
	std::vector<HttpBlock>	http_store_;
	std::vector<OtherBlock>	other_store_;
	std::map<std::string, std::string>	root_directives_;//key : derective, value : value
	std::string	file_name_;

	int	line_len_;
};

#endif
