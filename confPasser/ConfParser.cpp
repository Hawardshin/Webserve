# include "ConfParser.hpp"

//default_conf_file
ConfParser::ConfParser():file_name_("./default.conf") ,root_(""), index_(""), autoindex_(""){}
ConfParser::~ConfParser(){}
/**
 * @brief conf파일을 열어서 conf파일을 http_store에 저장해줍니다.
 * @details 각 conf파일의 구조에 맞게 클래스 내부에 블록들에 대한 저장을 가지고 있습니다.
 * 1. root에서 http 블록에 해당하는 모든 블록을 가지고 있고,
 * 2. http에서 모든 server 블록을
 * 3. server에서 모든 location을 가지고 있습니다.
 * 만약 http 블록이 없고 server block만 있는 경우 제가 self로 http 블록을 생성해주는 방식으로 갑니다.
 * (다만 http 블록은 한개만 가능하도록 하겠습니다.)
 * @warning 오류가 발생하면 invalid_argument가 throw 됩니다. (오류가 나도 close 처리는 해줬습니다.)
 */
void  ConfParser::confInit(){
	std::ifstream conf_file(file_name_);
	if (!conf_file.is_open())
		throw std::invalid_argument("Error : there is no conf_file\n");
	try{
		parseConf(conf_file);
	}
	catch(std::exception &e){
		std::cerr << e.what();
		conf_file.close();
		throw(std::invalid_argument(""));
	}
}

void  ConfParser::confPathInit(char* argv){
	file_name_ = argv;
}

void  ConfParser::parseConf(std::ifstream& input){
	std::string line;
	int line_len = 0;
	std::string directive = "";
	while (std::getline(input, line) ){
		line_len++;
		size_t dir_pos_a = line.find('{');
		size_t dir_pos_b = line.find(';');
		std::cout << line << "\n"  << std::endl;
		if (dir_pos_a == std::string::npos && dir_pos_b == std::string::npos){
			std::cout << "ss!!!1" << std::endl;
			std::cout << "|" <<line  << "|"<< "\n";
			trimComment(line);
			trimSidesSpace(line);
			if (line == "")//공백만 있거나 탭만 있는 경우
				continue;
			std::cerr << file_name_ << " : " << line_len;
			throw(std::runtime_error(" [ERROR in Nginx conf_file]"));
		}
		else if (dir_pos_b != std::string::npos && dir_pos_a == std::string::npos){
			// std::cout << "ss!!!2"  << std::endl;
			try{
				extractDirective(line.substr(0, dir_pos_b));
			}catch(std::exception &e){
				std::cerr <<e.what() << "\n";
				std::cerr << file_name_ << " : " << line_len;
				throw(std::runtime_error("[ERROR in Nginx confile]"));
			}
		}
		else{//짝이 맞는 중괄호가 나올 때까지 재귀적으로 들어간다.
			



		}
	}
}

/**
 * @brief 앞뒤로 스페이스바 삭제해주고 Directive를 추출합니다.
 * 이후 정상적인 코드라고 생각하고 그 값을 파싱해줍니다.
 * 여러개인 경우 space로 띄워져 있습니다.
 *
 * @param line ';'로 잘린 문자열이 들어옵니다.
 */
void  ConfParser::extractDirective(std::string line){

	std::string key, value;
	 //주석을 지워줍니다.

	trimComment(line);
	trimSidesSpace(line);
	std::cout << "line:|"<< line << "|\n";
	//스페이스를 기준으로 key와 value를 만든다음에 그값을 map에 넣어준다.
	size_t tmpos = line.find(' ');
	//directive를 잘랐는데 directive<space>value로 되어있어야 하기 때문에 아닌 경우에 대해서 처리해준 것입니다.
	if (tmpos == std::string::npos){
		throw(std::runtime_error("ERROR DIRECTIVE key"));
	}
	key = line.substr(0,tmpos);
	std::cout << "key:|"<< key << "|\n";
	for (; tmpos < line.size(); tmpos++){
		if (line[tmpos] != ' ' && line[tmpos] != '\t')
			break;
	}
	value = line.substr(tmpos);
	std::cout << "value:|"<< value << "|\n";
	if (key == "root")
		root_ = value;
	if (key == "index")
		index_ = value;
	if (key == "autoindex")
		autoindex_ = value;
	root_directives_[key] = value;
}
