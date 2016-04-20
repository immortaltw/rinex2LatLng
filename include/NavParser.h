#include <iostream>
#include <string>
#include "Ephemeris.h"

class NavParser {
public:
	NavParser(string filePath);
	Ephemeris& getEphemeris();
private:
	std::vector<Ephemeris> eph;
};