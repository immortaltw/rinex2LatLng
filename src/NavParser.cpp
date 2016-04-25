#include <fstream>
#include <sstream>
#include "NavParser.h"
#include "util.h"

void NavParser::parse() {
	std::ifstream fin(_filePath);
	std::string str;
	int state = 0;
	while(std::getline(fin, str)) {
		switch (state) {
		// Header parsing state.
		// Find iono alphas, betas and delta UTC.
		case 0:
			if (str.substr(_headerDataEndCol) != _headerEndStr) {
				std::string headerType = str.substr(_headerDataEndCol);
				if (headerType == _ionoAplhaStr) parseIonoAlpha(str);
				else if (headerType == _ionoBetaStr) parseIonoBeta(str);
				else if (headerType == _deltaUTCStr) parseDeltaUTC(str);
			} else state = 1;
			break;
		// Ephemeris parsing state.
		case 1:
			break;
		}
	}
}

void NavParser::parseIonoAlpha(std::string &line) {
	std::istringstream iss(line);
	std::string s;
	while (iss >> s) {
		Utility::fortranD2cpp(s);
		std::cout << s << std::endl;
	}
}

void NavParser::parseIonoBeta(std::string &line) {
	// std::cout << line << std::endl;
}

void NavParser::parseDeltaUTC(std::string &line) {
	// std::cout << line << std::endl;
}