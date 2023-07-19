# include "HttpBase.hpp"


HttpBase::HttpBase() :  root_(""), autoindex_(false), client_max_body_size_(-1), error_page_(""){}
HttpBase:: ~HttpBase(){}
