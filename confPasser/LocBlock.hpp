#ifndef LOCBLOCK_HPP
# define LOCBLOCK_HPP

# include "ParseTool.hpp"
# include "OtherBlock.hpp"
# include "IBlock.hpp"
# include "HttpBase.hpp"
/**
 * @brief location 블록 이 안에는 다른 블록은 오지 못하고 오직 limit_except 블록만 받도록 하겠습니다.
 *
 * @note [location 블록 주요 인자] cgi_pass, limit_except, return
 * @details [인자별 상세 설명]
 * cgi_pass : fastcgi인자와 비슷한 우리가 만든 인자입니다.
 * limit_except : 블록 형태로 들어오게 되고 location에서 사용할 메서드들을 제한합니다.
 * return : return 코드와 return_type으로 나눠서 저장해줍니다.
 */
class LocBlock : public IBlock, public HttpBase{
public:
	LocBlock(std::string loc_info);
	~LocBlock();
	std::map<std::string, std::string>& getDirStore();
	void	makeBlock(std::string line, std::ifstream& input, int& line_len_);
private:
	LocBlock();
	std::map<std::string, std::string> loc_directives_;

	std::string upload_store_;
	std::string loc_info_;//location / { 예시에서 : '/'를 이곳에 저장한다.
	int return_code_;
	std::string return_string_;
	bool is_limit_except_;
	std::string cgi_pass_;
	std::vector<std::string> deny_methods_;
};

#endif
