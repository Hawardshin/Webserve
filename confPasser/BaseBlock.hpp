#ifndef BASEBLOCK_HPP
# define BASEBLOCK_HPP
# include "ParseTool.hpp"
class BaseBlock
{
	public : BaseBlock();
	virtual ~BaseBlock();
protected :
	std::string root_;
	std::vector<std::string> index_;
	bool autoindex_;
	int client_max_body_size_;
	std::vector<int> error_code_;
	std::string error_page_;
};

#endif
