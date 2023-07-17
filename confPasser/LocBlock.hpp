#ifndef LOCBLOCK_HPP
# define LOCBLOCK_HPP


# include "ParseTool.hpp"
# include "OtherBlock.hpp"
class LocBlock{
public:
	LocBlock(std::string loc_info);
	~LocBlock();
	void	makeBlock(std::string line, std::ifstream& input, int& line_len_);
	std::map<std::string, std::string>& getDirStore();
private:
	LocBlock();
	std::vector<OtherBlock> other_store_;
	std::map<std::string, std::string> loc_directives_;
	std::string loc_info_;
	// bool root_;
	// bool index_;
	// bool autoindex_;
	// bool error_page_;
};

#endif
