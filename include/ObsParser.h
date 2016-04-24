#include <string>
#include <vector>
#include "ObsVars.h"

class ObsParser {
public:
	ObsParser(std::string filePath): _filePath(filePath) {
		std::cout << _filePath << std::endl;
	};
	void parse();
private:
	std::vector<ObsVars> obs;
	std::string _filePath;
};