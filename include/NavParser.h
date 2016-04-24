#include <iostream>
#include <string>
#include "Ephemeris.h"

class NavParser {
public:
	NavParser(string filePath);
	Ephemeris& getEphemeris(uint32_t time);
private:
	std::vector<Ephemeris> eph;
};