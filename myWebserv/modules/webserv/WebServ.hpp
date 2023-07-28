#ifndef WEBSERV_HPP
# define WEBSERV_HPP
# include "../config/ConfParser.hpp"
# include "../ServManager/ServManager.hpp"
class WebServ{
	public :
		void	startServer(int argc, char**argv);
	private:
		ConfParser config_parser_;
		ServManager manager_;
};

#endif
