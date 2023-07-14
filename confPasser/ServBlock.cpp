#include "ServBlock.hpp"

ServBlock::ServBlock(){

}
ServBlock::~ServBlock(){

}
//http에서 path에 해당합니다.
LocBlock ServBlock::findLocBlock(std::string path){
	(void)path;
	return loc_store_[0];
}
