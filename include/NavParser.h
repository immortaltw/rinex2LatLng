#include <iostream>
#include <string>
#include <vector>
#include "Ephemeris.h"

class NavParser {
public:
	NavParser(std::string filePath): _filePath(filePath) {
		_headerDataEndCol = 60;
		_ionoAplhaStr = "ION ALPHA";
		_ionoBetaStr = "ION BETA";
		_deltaUTCStr = "DELTA-UTC: A0,A1,T,W";
		_headerEndStr = "END OF HEADER";
	};
	void parse();
	Ephemeris& getEphemeris(uint32_t time);
private:
	void parseIonoAlpha(std::string &line);
	void parseIonoBeta(std::string &line);
	void parseDeltaUTC(std::string &line);

	int _headerDataEndCol;
	std::vector<Ephemeris> eph;
	std::string _filePath;
	std::string _ionoAplhaStr;
	std::string _ionoBetaStr;
	std::string _deltaUTCStr;
	std::string _headerEndStr;
	/**
	 * For ionospheric correction (Klobuchar model).
	 * Obtained from the header of a nav file.
	 */
	double alpha0;
	double alpha1;
	double alpha2;
	double alpha3;
	double beta0;
	double beta1;
	double beta2;
	double beta3;
};