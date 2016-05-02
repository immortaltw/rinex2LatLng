#include <iostream>
#include "ObsParser.h"
#include "NavParser.h"

int main() {
	std::cout<< "Test Launcher" << std::endl;

	// NavParser nParser(std::string("../../resources/brdc0760.16n"));
	// nParser.parse();

	ObsParser oParser(std::string("../../resources/farb0760.16o"));
	oParser.parse();
}