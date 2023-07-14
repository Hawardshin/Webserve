# include "ConfParser.hpp"

//default_conf_file
ConfParser::ConfParser():file_name_("./default.conf") ,root_(""), index_(""), autoindex_(""){}
ConfParser::~ConfParser(){}

void  ConfParser::confInit(){
	std::ifstream conf_file(file_name_);
	if (!conf_file.is_open())
		throw std::runtime_error("Error : there is no conf_file\n");
	try{
		parseConf(conf_file);
	}
	catch(std::exception &e){
		std::cerr << e.what();
		conf_file.close();
		throw(std::invalid_argument(""));
	}
}

void  ConfParser::confPathInit(char *argv){
  file_name_ = argv;
}


void  ConfParser::parseConf(std::ifstream &input){
	std::string line;
  int line_len = 0;
	std::string directive = "";
	while (std::getline(input, line)){
    line_len++;
		size_t dir_pos_a = line.find('{');
		size_t dir_pos_b = line.find(';');
		if (dir_pos_a == std::string::npos || dir_pos_b == std::string::npos){
      //공백만 있거나 탭만 있는 라인이 있다면 버려준다.
      //동시에 한줄에 ;나 { 가없다면 잘못 된 것으로 판단한다.
      if (line == "")
        continue;
      for (size_t i = 0;i < line.size();i++){
        if (line[i] != ' ' && line[i] != '\t'){
          // 예시 : /etc/nginx/nginx.conf:32
          std::cerr << file_name_ << " : " << line_len;
          throw(std::runtime_error("[ERROR in Nginx confile]"));
        }
      }
    }
		else if (dir_pos_b == std::string::npos && dir_pos_a != std::string::npos){
      try{
        extractDirective(line.substr(0, dir_pos_a));
      }catch(std::exception &e){
        std::cerr <<e.what() << "\n";
        std::cerr << file_name_ << " : " << line_len;
        throw(std::runtime_error("[ERROR in Nginx confile]"));
      }

		}
	}
}

/**
 * @brief 앞뒤로 스페이스바 삭제해주고 Directive를 추출합니다.
 * 이후 정상적인 코드라고 생각하고 그 값을 파싱해줍니다.
 *
 * @param line ';'로 잘린 문자열이 들어옵니다.
 */
void  ConfParser::extractDirective(std::string line){
	size_t i;
  std::string key, value;
   //주석을 지워줍니다.
  size_t tmpos = line.find('#');
  if (tmpos != std::string::npos)
    line = line.substr();

  //앞쪽에 스페이스 지운다.
	for (i = 0; i < line.size();	i++){
		if (line[i] != '\t' && line[i] != ' ')
      break;
	}
  line = line.substr(i);

  //뒤쪽의 스페이스와 tab 을 다 지운다.
  for (i = line.size() -1; i > 0; i--){
    if (line[i] != '\t' && line[i] != ' ')
        break;
  }
  line = line.substr(0, i);

  //스페이스를 기준으로 key와 value를 만든다음에 그값을 map에 넣어준다.
  tmpos = line.find(' ');
  //directive를 잘랐는데 directive<space>value로 되어있어야 하기 때문에 아닌 경우에 대해서 처리해준 것입니다.
  if (tmpos == std::string::npos){
    throw(std::runtime_error("ERROR DIRECTIVE key"));
  }
  key = line.substr(0,tmpos);
  value = line.substr(tmpos);
  if (value.find(' ') != std::string::npos)
    throw(std::runtime_error("ERROR DIRECTIVE value"));
  if (key == "root")
    root_ = value;
  if (key == "index")
    index_ = value;
  if (key == "autoindex")
    autoindex_ = value;
  root_directives_[key] = value;

}
