#include <iostream>
#include <string>
#include <map>
class Client{
	public :
	private:
		int clnt_fd_;
		HttpRequestInfo http_info_;
		CGI cgi_info_;
};

class HttpRequestInfo{

	private:
		std::string method_;
		std::map<std::string, std::string> headers_;
		char* body_;
		std::string str_body_;
};

class CGI {

};
