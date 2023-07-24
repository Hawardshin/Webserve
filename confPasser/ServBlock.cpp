#include "ServBlock.hpp"

/**
 * @brief Construct a new Serv Block:: Serv Block object
 * default listen은 -1번으로 해서 에러로 처리할 예정입니다.
 *
 */
ServBlock::ServBlock() : upload_store_(""), listen_(-1){}

ServBlock::~ServBlock(){}

/**
 * @brief serv_directives_ 반환
 *
 * @note 템플릿 사용 위해서 반드시 필요
 * @return std::map<std::string, std::string>& 인자로 받아서 변경시키기 위해서 레퍼런스 타입으로 반환함
 */
std::map<std::string, std::string>& ServBlock::getDirStore(){return (serv_directives_);}
const std::string& ServBlock::getUploadStore(){return upload_store_;}
const std::vector<std::string>& ServBlock::getServerName(){return server_name_;}
const int& ServBlock::getListen(){return listen_;}


/**
 * @brief 블록을 만드는 함수 LocBlock 블록과 otherBlock허용
 *
 * @param line 파싱중인 한줄 라인(주석과 스페이스를 삭제한)
 * @param input 파싱중인 설정파일
 * @param line_len_ 설정파일을 어디까지 읽었는지 확인
 * @note 템플릿 사용을 위해 반드시 필요
 * @warning  http, SERVER 블록은 에러로 감지함
 */
void	ServBlock::makeBlock(std::string line, std::ifstream& input, int& line_len_){
	size_t pos = line.find('{');
	std::string block_name = line.substr(0, pos);
	trimSidesSpace(block_name);
	// std::cout << "5. |" << block_name << "|"<< std::endl;
	if (pos != line.size() - 1 || block_name == "")
		throw(std::runtime_error("this is not block"));
	switch(checkBlockName(block_name)){
		case HTTP :throw(std::runtime_error("this is not GOOD HTTP block"));
		case SERVER : throw(std::runtime_error("this is not GOOD SERVER block"));
		case LOCATION : makeLocBlock(input, line_len_, block_name);
			break;
		case OTHERBLOCK : makeOtherBlock(input, line_len_);
			break;
	}
}

/**
 * @brief 모든 server block의 데이터를 사용가능하도록 map에 담긴걸 클래스 멤버에 사용하기 좋은 값으로 담아주는 함수
 *
 */
void	ServBlock::refineAll(){
	parseHttpDirective(serv_directives_);
	parseServDirective();
	if (loc_store_.size() == 0)
		throw(std::runtime_error("You must input Locaction block least One Block!"));
	for (size_t i = 0; i < loc_store_.size(); i++){
		loc_store_[i].refineAll();
	}
}

void	ServBlock::printInfo(){
	printHttpInfo();
	std::cout << "\n---------------[Server]------------------\n";
	std::cout << "upload_store_:|" << upload_store_ << "|\n";
	std::cout << "[server_name_]\n";
	for (size_t i = 0;i < server_name_.size(); i++){
			std::cout << "server_name_[" << i << "]:|" << server_name_[i] << "|\n";
	}
	std::cout << "listen:|" << listen_ << "|\n";
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

/*private*/

/**
 * @brief 로케이션 블록을 만드는 함수
 *
 * @param input 열어둔 설정파일
 * @param line_len_ 설정파일 읽은 길이
 * @note 재귀적으로 돌기 위한 템플릿 함수 parseUntilEnd를 호출한다.
 */
void	ServBlock::makeLocBlock(std::ifstream& input, int& line_len_, std::string& block_name){
	if (block_name == "location")
		throw(std::runtime_error("location block Don't have pathinfo"));
	std::string loc_info =  block_name.substr(8);
	trimSidesSpace(loc_info);
	LocBlock new_block(loc_info);
	loc_store_.push_back(new_block);
	parseUntilEnd(input, line_len_, loc_store_[loc_store_.size() - 1]);
}

/**
 * @brief Other 블록을 만드는 함수
 *
 * @param input 열어둔 설정파일
 * @param line_len_ 설정파일 읽은 길이
 * @note 재귀적으로 돌기 위한 템플릿 함수 parseUntilEnd를 호출한다.
 */
void	ServBlock::makeOtherBlock(std::ifstream& input, int& line_len_){
	OtherBlock new_block;
	other_store_.push_back(new_block);
	parseUntilEnd(input, line_len_, other_store_[other_store_.size() - 1]);
}

/**
 * @brief 서버에만 해당하는 데이터를 멤버변수에 담아주는 함수
 * @details server_name이 설정 안되는 경우가 존재할 수 있다.
 * [subject] : Setup the server_names or not.
 */
void	ServBlock::parseServDirective(){
	std::map<std::string, std::string>::iterator it = serv_directives_.find("server_name");
	if (it == serv_directives_.end())
		server_name_.push_back("");
		// throw(std::runtime_error("You must at least one server_name!!!"));
	splitAndStore(server_name_, (*it).second, ' ');
	it = serv_directives_.find("listen");//default_server안 받겠습니다.
	if (it == serv_directives_.end())
		throw(std::runtime_error("You must at least one listen!!!"));
	listen_ = stringToInt((*it).second);
	it = serv_directives_.find("upload_store");
	if (it != serv_directives_.end())
		upload_store_ = (*it).second;
}

