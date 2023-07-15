#ifndef LOCBLOCK_HPP
# define LOCBLOCK_HPP


# include "ParseTool.hpp"
# include "OtherBlock.hpp"
class LocBlock{
public:
	LocBlock();
	// explicit LocBlock();

	~LocBlock();

private:
	std::vector<OtherBlock> other_store_;
	std::map<std::string, std::string> loc_directives_;
	std::string root_;
	std::string index_;
	std::string autoindex_;
	std::string error_page_;
	
};

#endif
