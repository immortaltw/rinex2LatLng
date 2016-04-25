#include <iostream>
#include <string>

class Utility {
public:
	static double fortranD2cpp(std::string &fortranD);
};

double Utility::fortranD2cpp(std::string &fortranD) {
	std::size_t pos = fortranD.find("D");
	std::string digits = fortranD.substr(0, pos);
	std::string power = fortranD.substr(pos+1);
	std::cout << digits << " " << power << std::endl;
	return 0.0;
}