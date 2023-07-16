# include "ConfParser.hpp"

//public
//default_conf_file
ConfParser::ConfParser():file_name_("./default.conf"), line_len_(0), root_(false), index_(false), autoindex_(false), error_page_(false){}

ConfParser::~ConfParser(){}

/**
 * @brief 파일이름이 있는 경우만 호출합니다.
 *
 * @param argv 파일의 경로
 */
void	ConfParser::confPathInit(char* argv){
	file_name_ = argv;
}

/**
 * @brief conf파일을 열어서 conf파일을 http_store 벡터에 저장해줍니다.
 * (http안에서 serv_block, serv_block안에 loc_block까지 다 채우기)
 * @details 각 conf파일의 구조에 맞게 클래스 내부에 블록들에 대한 저장을 가지고 있습니다.
 * 1. root에서 http 블록에 해당하는 모든 블록을 가지고 있고,
 * 2. http에서 모든 server 블록을
 * 3. server에서 모든 location을 가지고 있습니다.
 * 만약 http 블록이 없고 server block만 있는 경우 제가 self로 http 블록을 생성해주는 방식으로 갑니다.
 * (다만 http 블록은 한개만 가능하도록 하겠습니다.)
 * @warning 오류가 발생하면 invalid_argument가 throw 됩니다. (오류가 나도 close 처리는 해줬습니다.)
 */
void  ConfParser::confInit(){
	std::ifstream conf_file(file_name_.c_str());
	if (!conf_file.is_open())
		throw std::invalid_argument("Error : there is no conf_file\n");
	try{
		parseConf(conf_file);
	}
	catch(std::exception &e){
		std::cerr << file_name_ << " : " << line_len_ << "\n";
		std::cerr << e.what() << "\n";
		conf_file.close();
		throw(std::invalid_argument(""));
	}
}

/**
 * @brief 새로운 블록을 만드는 함수 블록은 오직 "http {"
 * 또는 "블록_이름 {" 로 들어오는 것만 올바른 블록이라 인식했습니다.
 *
 * @param line "블록 명{" 이렇게 들어온 한 줄
 * @param input 열어 ifstream으로 열어둔 conf파일
 */
void	ConfParser::makeBlock(std::string line, std::ifstream& input){
	size_t pos = line.find('{');
	std::string block_name = line.substr(0, pos);
	trimSidesSpace(block_name);
	std::cout << "5. |" << block_name << "|"<< std::endl;;
	(void)input;
	if (pos != line.size() - 1 || block_name == "")
		throw(std::runtime_error("block name in ERROR"));
	switch(check_blockname(block_name)){
		case HTTP : makeHttpBlock(input);
			break;
		case SERVER : throw(std::runtime_error("You need to create an HTTP block first.(server)"));
		case LOCATION : throw(std::runtime_error("You need to create an HTTP block first.(location)"));
		case OTHER : makeOtherBlock(input);
			break;
	}
}

/**
 * @brief Get the root_directives_ 클래스 멤버를 반환해서 레퍼런스로 사용하려고 다음과 같은 함수를 반들었습니다.
 *
 * @return std::map<std::string, std::string>& 클래스 맴버인 map 레퍼런스
 */
std::map<std::string, std::string>& ConfParser::getDirStore(){
	return (root_directives_);
}

/**
 * @brief HTTP 블록을 만드는 함수
 * @warning HTTP는 오직 1개의 블록만 올 수 있습니다.
 *
 * @param input
 */
void	ConfParser::makeHttpBlock(std::ifstream& input){
	if (http_store_.size() != 0)
		throw(std::runtime_error("there are two http block!!"));
	HttpBlock new_block;
	http_store_.push_back(new_block);
	parseUntilEnd(input, line_len_, new_block);
}

void	ConfParser::makeOtherBlock(std::ifstream& input){
	OtherBlock new_block;
	other_store_.push_back(new_block);
	parseUntilEnd(input, line_len_, new_block);
}


/**
 * @brief 메인로직 conf파일을 하나의 파일에 담아줍니다.
 * @details [블록 파싱 규칙]
 * 1. 블록은 "server {"  이런식으로 생긴 것만 생각합니다.
 * [ex]
  server
  # hi
  # hello
  {
  }
  이런식으로 되있는 경우는 아에 안되는 것으로 처리하겠습니다.
	ex : server{location{}} 이렇게 오는것도 안 합니다.
	 @warning runtime_error를 던집니다.
 * @param input ifstream으로 연 파일
 */
void  ConfParser::parseConf(std::ifstream& input){
	std::string line;
	std::string directive = "";
	while (std::getline(input, line)){
		trimComment(line);
		trimSidesSpace(line);
		line_len_++;
		if (line == "")
			continue;
		size_t dir_pos_a = line.find('{');
		size_t dir_pos_b = line.find(';');
		size_t dir_pos_c = line.find('}');
		std::cout << "2. line|"<< line << "|" << std::endl;
		if (dir_pos_c != std::string::npos || \
					(dir_pos_a == std::string::npos && dir_pos_b == std::string::npos)  || \
					(dir_pos_a != std::string::npos && dir_pos_b != std::string::npos))
			throw(std::runtime_error(" [ERROR in Nginx conf_file]"));
		else if (dir_pos_b != std::string::npos && dir_pos_a == std::string::npos)
				extractDirective(line.substr(0, dir_pos_b),root_directives_);
		else // {가 나오는 경우
			makeBlock(line, input);
	}
}


