#include "ServBlock.hpp"
/**
 * @brief Construct a new Serv Block:: Serv Block object
 * default listen은 8000번으로 했습니다.
 *
 */
ServBlock::ServBlock() : root_(false), index_(false), autoindex_(false), error_page_(false),server_name_(""), listen_(8000),default_server_(false) {

}
ServBlock::~ServBlock(){

}

/**
 * @brief 전달된 경로에 대해서 어떤 규칙을 따라야 하는지 리턴해주는 함수입니다.
 *
 * @param http에서 path를 추출해서 원하는 블럭을 얻을 때 사용합니다.
 * @return LocBlock 전딜힌 path에 대해서 해당하는 location block을 리턴해줍니다.
 */
LocBlock ServBlock::findLocBlock(std::string path){
	(void)path;
	return loc_store_[0];
}

std::map<std::string, std::string>& ServBlock::getDirStore(){
	return (serv_directives_);
}
