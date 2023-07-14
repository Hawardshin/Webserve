#ifndef SERVBLOCK_HPP
# define SERVBLOCK_HPP
# include "LocBlock.hpp"

class ServBlock
{
public:
  ServBlock();
  // explicit ServBlock();
  ~ServBlock();
  LocBlock findLocBlock(std::string path);//http에서 path에 해당합니다.
private:
  std::vector<LocBlock> loc_store_;
  std::map<std::string, std::string> serv_directives_;
};

#endif

