#include <iostream>
#include "ObsParser.h"
#include "NavParser.h"

int main() {
	std::cout<< "Test Launcher" << std::endl;

	NavParser nParser(std::string("../../resources/brdc0760.16n"));
	nParser.parse();

	ObsParser oParser(std::string("../../resources/farb0760.16o"));
	oParser.parse();

	std::cout << "Parsing o and n files done." << std::endl;
	std::cout << "Calculating the location of first 10 observations." << std::endl;

	std::vector<ObsVars> obs = oParser.getObs();

	for (int i=0; i<10; ++i) {
		ObsVars _curObs = obs[i];
		Ephemeris eph = nParser.getEphemeris(1144800000, 8);
	}
}