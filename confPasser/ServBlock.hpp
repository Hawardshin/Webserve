#ifndef SERVBLOCK_HPP
# define SERVBLOCK_HPP
# include "LocBlock.hpp"

class ServBlock{
public:
	ServBlock();
	~ServBlock();
	std::map<std::string, std::string>& getDirStore();
	void	makeBlock(std::string line, std::ifstream& input, int& line_len_);
	LocBlock findLocBlock(std::string path);//http에서 path에 해당합니다.

private:
	void	makeLocBlock(std::ifstream& input, int& line_len_);
	void	makeOtherBlock(std::ifstream& input, int& line_lne_);
	std::vector<LocBlock> loc_store_;
	std::vector<OtherBlock> other_store_;
	std::map<std::string, std::string> serv_directives_;
	bool root_;
	bool index_;
	bool autoindex_;
	bool error_page_;

	//only server member
	std::string server_name_;
	int listen_;
	bool default_server_;
};

#endif

