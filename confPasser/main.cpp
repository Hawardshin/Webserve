#include "ConfParser.hpp"


int main(int argc, char **argv){
	try{
		ConfParser::getInstance().configParseAll(argc, argv);
		const std::vector<int> &l_ports = ConfParser::getInstance().getListenPorts();
		for (size_t i =0; i < l_ports.size(); i++){
			std::cout << "Port num :" << l_ports[i] << "\n";
		}
		ServBlock tmp = ConfParser::getInstance().getServBlock(8080, "localhost");
		tmp.printInfo();
		std::cout << "--------------------------loccccccc-----------------------------\n";
		tmp.findLocBlock("/.pyth").printInfo();
	}catch (std::exception &e){
		std::cerr << e.what() << "\n";
	}
}
