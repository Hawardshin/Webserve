#ifndef HTTPBASE_HPP
# define HTTPBASE_HPP
# include "ParseTool.hpp"
class HttpBase
{
public :
	HttpBase();
	virtual ~HttpBase();
	void	parseHttpDirective(std::map<std::string, std::string>& dir_store);
	const char* directives_[6];
protected :
	void	setAutoIndex(const std::string& value);
	void	setErrorPage(const std::string& line);
	std::string root_;
	std::vector<std::string> index_;
	bool autoindex_;
	int client_max_body_size_;
	std::vector<int> error_code_;
	std::string error_page_;
};

#endif
