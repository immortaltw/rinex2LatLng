#include <iostream>
#include "ObsParser.h"

int main() {
	std::cout<< "Test Launcher" << std::endl;

	ObsParser oParser(std::string("/Users/immortal/Dev/projects/rinex2LatLng/resources/farb0760.16o"));
	oParser.parse();
}