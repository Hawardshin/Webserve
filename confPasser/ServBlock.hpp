#ifndef SERVBLOCK_HPP
# define SERVBLOCK_HPP
# include "LocBlock.hpp"

class ServBlock{
public:
	ServBlock();
	// explicit ServBlock();
	~ServBlock();
	LocBlock findLocBlock(std::string path);//http에서 path에 해당합니다.
private:
	std::vector<LocBlock> loc_store_;
	std::vector<OtherBlock> other_store_;
	std::map<std::string, std::string> serv_directives_;
	std::string root_;
	std::string index_;
	std::string autoindex_;
	std::string error_page_;

	//only server member
	std::string server_name_;
	std::string listen_;
	bool default_server_;
};

#endif

