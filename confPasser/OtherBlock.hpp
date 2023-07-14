#ifndef OTHERBLOCK_HPP
# define OTHERBLOCK_HPP
# include "ParseTool.hpp"
class OtherBlock{
	public :
		std::string block_name_;
	private :
		std::vector<OtherBlock> other_store_;
		std::map<std::string, std::string> other_directives_;
};

#endif
