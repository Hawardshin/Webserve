#include "ConfParser.hpp"


int main(int argc, char **argv){
	


		ServBlock tmp = test.getServBlock(8080, "localhost");
		tmp.printInfo();
		std::cout << "--------------------------loccccccc-----------------------------\n";
		tmp.findLocBlock("/.pyth").printInfo();

	}catch (std::exception &e){
		std::cerr << e.what() << "\n";
	}
}
