#include <iostream>
#include "ObsParser.h"

int main() {
	std::cout<< "Test Launcher" << std::endl;

	ObsParser oParser(std::string("../resources/farb0760.o"));
	oParser.parse();
}