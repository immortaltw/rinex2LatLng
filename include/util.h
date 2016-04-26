#include <iostream>
#include <string>
#include <cmath>

class Utility {
public:
	static double fortranD2cppD(std::string &fortranD);
};

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