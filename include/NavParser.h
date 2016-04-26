#include <iostream>
#include <string>
#include <vector>
#include "Ephemeris.h"

class NavParser {
public:
	NavParser(std::string filePath): _filePath(filePath) {
		_headerDataEndCol = 60;
		_ephLines = 8;
		_ionoAplhaStr = "ION ALPHA";
		_ionoBetaStr = "ION BETA";
		_deltaUTCStr = "DELTA-UTC: A0,A1,T,W";
		_headerEndStr = "END OF HEADER";
	};
	void parse();
	Ephemeris& getEphemeris(uint32_t time);
private:
	void _parseIonoAlpha(std::string &line);
	void _parseIonoBeta(std::string &line);
	void _parseDeltaUTC(std::string &line);

	void _internalLineParser(std::string &line, std::vector<double> &container);
	void _ephLineParser(std::vector<std::string> &lines, Ephemeris &eph);
	void _fillEph(int nthLine, Ephemeris &eph, std::vector<std::string> &lineV);

	int _headerDataEndCol;
	int _ephLines;
	std::vector<Ephemeris> _ephemeris;
	std::string _filePath;
	std::string _ionoAplhaStr;
	std::string _ionoBetaStr;
	std::string _deltaUTCStr;
	std::string _headerEndStr;
	/**
	 * For ionospheric correction (Klobuchar model).
	 * Obtained from the header of a nav file.
	 */
	std::vector<double> _alphas;
	std::vector<double> _betas;
	std::vector<double> _deltaUTC;
};