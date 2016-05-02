#include <string>
#include <vector>
#include "ObsVars.h"

// ~16MB ram for farb0760.16o
class ObsParser {
public:
	ObsParser(std::string filePath): _filePath(filePath) {
		_typesOfObsStr = "# / TYPES OF OBSERV";
		_headerEndStr = "END OF HEADER";
		_approxXYZStr = "APPROX POSITION XYZ";
		_headerDataEndCol = 60;
	};
	void parse();
private:
	std::vector<ObsVars> obs;
	std::string _filePath;
	std::string _typesOfObsStr;
	std::string _headerEndStr;
	std::string _approxXYZStr;

	int _headerDataEndCol;
	int _numOfObs;
	int _numOfLinesForObs;
	int _C1Locator;

	double _x0;			// Approximate X location
	double _y0;			// Approximate Y location
	double _z0;			// Approximate Z location

	void _parseTypesOfObs(std::string &line);
	void _parseApproxXYZ(std::string &line);
	int _parseFirstLineOfObs(std::string &line, ObsVars &curObs, int &epochFlag);
	void _parseObs(std::string &line, ObsVars &curObs, int curLineNum);
};