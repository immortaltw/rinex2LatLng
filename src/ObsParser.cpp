#include <fstream>
#include "ObsParser.h"
#include "util.h"

// Entry point of o file parsing.
void ObsParser::parse() {
	std::ifstream fin(_filePath);
	std::string str;
	int state = 0;
	int totalLines = 0;
	int curLineCnt = 1;
	int epochFlag = 0;
	int  obsCount = 0;
	ObsVars curObs;

	while(std::getline(fin, str)) {
		switch (state) {
		// State 0: header parsing.
		case 0:
		{
			std::string curHeaderType = str.substr(_headerDataEndCol);
			if (curHeaderType != _headerEndStr) {
				// Locate L1 C/A code pseudorange.
				if (curHeaderType == _typesOfObsStr) {
					_parseTypesOfObs(str);
				} else if (curHeaderType == _approxXYZStr) {
					_parseApproxXYZ(str);
				}
			} else state = 1;
			break;
		}
		// Parse first line of all obs.
		case 1:
		{
			totalLines = _parseFirstLineOfObs(str, curObs, epochFlag);
			state = 2;
			break;
		}
		// Parse current eph
		case 2:
		{
			if (curLineCnt == totalLines) state = 3;
			else {
				// if (epochFlag == 0) _parseObs(str, curObs, curLineCnt);
				curLineCnt++;
			}
			break;
		}
		// End of current obs parsing.
		// Add curObs to obs list and jump to next one.
		case 3:
		{
			// if (epochFlag == 0) this->obs.push_back(curObs);
			curObs.clear();
			state = 2;
			curLineCnt = 1;
			obsCount++;
			totalLines = _parseFirstLineOfObs(str, curObs, epochFlag);
			break;
		}
		default:
			break;
		}
	}

	std::cout << obsCount << std::endl;
}

// Fetch the index where L1 C/A-code pseudoreange locates.
void ObsParser::_parseTypesOfObs(std::string &line) {
	std::string _obsStr = line.substr(0, _headerDataEndCol-1);
	this->_numOfObs = std::stoi(_obsStr.substr(0, 6));

	// 9 cols were preserved for types of obs.
	int i;
	std::string res;
	for (i=1; i<=9 && res.find("C1") == std::string::npos; ++i) {
		res = _obsStr.substr(i*6, 6);
	}
	this->_C1Locator = i-1;
}

void ObsParser::_parseApproxXYZ(std::string &line) {
	std::string _xyzStr = line.substr(0, _headerDataEndCol-1);
	this->_x0 = std::stod(_xyzStr.substr(0, 14));
	this->_y0 = std::stod(_xyzStr.substr(14, 14));
	this->_z0 = std::stod(_xyzStr.substr(28, 14));
}

// Naively assume that all SVs are GPS.
// If epoch flag != 0, then ditch the obs.
// @return: {int} total line # of current obs.
int ObsParser::_parseFirstLineOfObs(std::string &line, ObsVars &curObs, int &epochFlag) {
	// First line is vital for correctly locating all the later obs.
	double y = std::stod(line.substr(0, 3));
	double m = std::stod(line.substr(3, 3));
	double d = std::stod(line.substr(6, 3));
	double h = std::stod(line.substr(9, 3));
	double min = std::stod(line.substr(12, 3));
	double s = std::stod(line.substr(15, 11));
	double timeOfEpoch = Utility::secondsFromGPSBegin(y, m, d, h, min, s);

	epochFlag = std::stoi(line.substr(26, 3));

	int numOfSv = std::stoi(line.substr(29, 3));

	double dt = 0;
	if (line.size() > 68) {
		if (line.substr(69) != "") dt = std::stod(line.substr(69));
	}

	return (this->_numOfObs <= 5)? numOfSv: numOfSv*2;
}

void ObsParser::_parseObs(std::string &line, ObsVars &curObs, int curLineNum) {

}

