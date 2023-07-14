#ifndef LOCBLOCK_HPP
# define LOCBLOCK_HPP

# include <fstream>
# include <sstream>
# include <iostream>
# include <string>
# include <vector>
# include <map>

class LocBlock{
public:
  LocBlock();
  // explicit LocBlock();

  ~LocBlock();

private:

  std::map<std::string, std::string> loc_directives_;
};

#endif
