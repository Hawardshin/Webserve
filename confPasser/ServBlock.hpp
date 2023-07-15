#ifndef SERVBLOCK_HPP
# define SERVBLOCK_HPP
# include "LocBlock.hpp"

class ServBlock{
public:
	ServBlock();
	~ServBlock();
	LocBlock findLocBlock(std::string path);//http에서 path에 해당합니다.
	void	makeBlock(std::string line, std::ifstream& input);
private:
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

