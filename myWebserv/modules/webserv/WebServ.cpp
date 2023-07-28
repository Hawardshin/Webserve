# include "WebServ.hpp"

void	WebServ::startServer(int argc, char** argv){
	config_parser_.configParseAll(argc, argv);
}

