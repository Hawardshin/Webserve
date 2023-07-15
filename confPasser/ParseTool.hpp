#ifndef PARSETOOL_HPP
# define PARSETOOL_HPP
# include <fstream>
# include <sstream>
# include <iostream>
# include <string>
# include <vector>
# include <map>
# include <algorithm>


typedef enum blocktype{
		HTTP,
		SERVER,
		LOCATION,
		OTHER,
}e_block;

void	trimSidesSpace(std::string &line);
void	trimComment(std::string &line);
void	splitKeyVal(std::string& key, std::string &value, std::string &line);

e_block	check_blockname(std::string block_name);
#endif
