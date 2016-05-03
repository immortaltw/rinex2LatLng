#include <iostream>
#include <cmath>
#include <ctime>

#include "util.h"

double Utility::fortranD2cppD(std::string &fortranD) {
	std::size_t pos = fortranD.find("D");
	std::string digits = fortranD.substr(0, pos);
	std::string sign = fortranD.substr(pos+1, 1);
	std::string factor = fortranD.substr(pos+2);

	// Great!! c++ already provides us a nice little string to double tool!
	double res = std::stod(digits);
	double factorD = pow(10, std::stod(factor)); // Overflow?

	// minus sign: divide.
	if (sign == "-") {
		// And string to interger!!! Nice!!!
		res /= factorD;
	}
	// plus sign: multiply. 
	else {
		// Overflow?
		res *= factorD;
	}
	return res;
}

// Not very robust.
double Utility::secondsFromGPSBegin(double y, double m, double d,
									  double h, double min, double s) {
	struct tm tGPS = {0};
	struct tm tN = {0};
	// Zero time-point of GPS is defined as 12:00am of 1/6/1980.
	tGPS.tm_year = 80;
	tGPS.tm_mon = 0;
	tGPS.tm_mday = 6;
	tGPS.tm_hour = 0;
	tGPS.tm_min = 0;
	tGPS.tm_sec = 0;

	tN.tm_year = y<80? y+100: y;
	tN.tm_mon = m;
	tN.tm_mday = d;
	tN.tm_hour = h;
	tN.tm_min = min;
	tN.tm_sec = s;

	return difftime(mktime(&tN), mktime(&tGPS));
}