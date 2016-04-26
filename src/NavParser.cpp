#include <fstream>
#include <sstream>
#include "NavParser.h"
#include "util.h"

void NavParser::parse() {
	std::ifstream fin(_filePath);
	std::string str;
	int state = 0;
	int ephLineCnt = 0;
	std::vector<std::string> lines;

	while(std::getline(fin, str)) {
		switch (state) {
		// Header parsing state.
		// Find iono alphas, betas and delta UTC.
		case 0:
			if (str.substr(_headerDataEndCol) != _headerEndStr) {
				std::string headerType = str.substr(_headerDataEndCol);
				if (headerType == _ionoAplhaStr) _parseIonoAlpha(str);
				else if (headerType == _ionoBetaStr) _parseIonoBeta(str);
				else if (headerType == _deltaUTCStr) _parseDeltaUTC(str);
			} else state = 1;
			break;
		// Ephemeris parsing state.
		// Fill in the rest lines to vectors of ephemeris struct.
		// By observation, ephemeris of each SV in specific time epoch takes 8 lines. 
		case 1:
			if (ephLineCnt == this->_ephLines) {
				for (auto s: lines) std::cout << s << std::endl;
				std::cout << "----------------------------------" << std::endl;
				Ephemeris eph;
				_ephLineParser(lines, &eph);
				// _ephemeris.push_back(eph);
				ephLineCnt = 1;
				lines.clear();
			} else {
				ephLineCnt++;
			}
			lines.push_back(str);
			break;
		}
	}
}

void NavParser::_parseIonoAlpha(std::string &line) {
	_internalLineParser(line, _alphas);
}

void NavParser::_parseIonoBeta(std::string &line) {
	_internalLineParser(line, _betas);
}

void NavParser::_parseDeltaUTC(std::string &line) {
	_internalLineParser(line, _deltaUTC);
}

// Seem like a good timing to use tempalte?
void NavParser::_internalLineParser(std::string &line, std::vector<double> &container) {
	std::istringstream iss(line);
	std::string s;
	while (iss >> s) {
		// Very C-ish and naive way to determine if s is numeric.
		if (!isdigit(s.c_str()[0]) && s.c_str()[0] != '-') continue;

		if (s.find("D") == std::string::npos) {
			container.push_back(std::stod(s));
		} else {
			container.push_back(Utility::fortranD2cppD(s));
		}
	}
}

void NavParser::_ephLineParser(std::vector<std::string> &lines, Ephemeris &eph) {
	for (int i=0; i<lines.size(); ++i) {
		std::istringstream iss(lines[i]);
		std::string s;
		std::vector<std::string> lineV;
		while (iss >> s) {
			lineV.push_back(s);
		}

	}
}

void NavParser::_fillEph(int nthLine, Ephemeris &eph, std::vector<std::string> &lineV) {
	switch(nthLine) {
	// First line.
	case 0:
		eph.PRN = lineV[0];
		break;
	}
}
