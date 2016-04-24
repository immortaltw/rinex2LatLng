#include <fstream>
#include "ObsParser.h"

void ObsParser::parse() {
	std::ifstream fin(_filePath);
	std::string str;
	while(std::getline(fin, str)) {
		std::cout << str << std::endl;
	}
}