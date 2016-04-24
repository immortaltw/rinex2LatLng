#include <iostream>
#include "ObsParser.h"
#include "NavParser.h"

int main() {
	std::cout<< "Test Launcher" << std::endl;

	NavParser nParser(std::string("/Users/immortal/Dev/projects/rinex2LatLng/resources/brdc0760.16n"));
	nParser.parse();
}