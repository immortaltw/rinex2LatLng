#ifndef utility_h
#define utility_h

#include <string>
#include <vector>
#include "Ephemeris.h"

struct SatPos {
	double x;
	double y;
	double z;
};

class Utility {
public:
	static double fortranD2cppD(std::string &fortranD);
	static double secondsFromGPSBegin(double y, double m, double d,
									  double h, double min, double s);
	static SatPos computeSatPos(double GPSTime, Ephemeris &eph);
	static std::vector<double> ecef2lla(SatPos &pos);
};


#endif