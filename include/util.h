#ifndef utility_h
#define utility_h

#include <string>

class Utility {
public:
	static double fortranD2cppD(std::string &fortranD);
	static double secondsFromGPSBegin(double y, double m, double d,
									  double h, double min, double s);
};


#endif