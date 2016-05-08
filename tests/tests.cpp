#include <iostream>
#include <armadillo>
#include "ObsParser.h"
#include "NavParser.h"
#include "util.h"

using namespace arma;

int main() {
	std::cout<< "Test Launcher" << std::endl;
	std::cout << Utility::secondsFromGPSBegin(16, 0, 6, 0, 0, 0) << std::endl;

	SatPos pos;
	pos.x = -2658220.5;
	pos.y = -4138072.8;
	pos.z = 4049411.8;
	std::vector<double> res = Utility::ecef2lla(pos);
	std::cout << res[0]*180/M_PI << " "
			  << res[1]*180/M_PI << " "
			  << res[2] << std::endl;

	NavParser nParser(std::string("../../resources/brdc0760.16n"));
	nParser.parse();

	ObsParser oParser(std::string("../../resources/farb0760.16o"));
	oParser.parse();
}