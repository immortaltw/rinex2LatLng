#include <fstream>
#include <sstream>
#include "NavParser.h"
#include "util.h"

// Entry point of n file parsing task.
// Nothing magical here..
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
				// for (auto s: lines) std::cout << s << std::endl;
				// std::cout << "----------------------------------" << std::endl;
				Ephemeris eph;
				_ephLineParser(lines, eph);
				this->_ephemeris.push_back(eph);
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

Ephemeris& NavParser::getEphemeris(double toc, int PRN) {
	std::vector<Ephemeris *> ephForPRN;
	for (int i=0; i<this->_ephemeris.size(); ++i) {
		if (this->_ephemeris[i].PRN == PRN) {
			ephForPRN.push_back(&this->_ephemeris[i]);
		}
	}

	// return *ephForPRN[0];
	// Binary search, since toc is sorted.
	int begin = 0;
	int len = ephForPRN.size()-1;
	int end = len;
	int mid = begin;
	while (begin+1<end) {
		mid = end-((end-begin)/2);
		if (ephForPRN[mid]->toc > toc) {
			end = mid;
		} else if (ephForPRN[mid]->toc < toc) {
			begin = mid;
		} else break;
	}
	return *ephForPRN[begin];
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
// This method is for parsing the header.
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

// This method is for parsing the eph groups. (every 8 lines).
void NavParser::_ephLineParser(std::vector<std::string> &lines, Ephemeris &eph) {
	for (int i=0; i<lines.size(); ++i) {
		_fillEph(i, eph, lines[i]);
	}
}

// This is ugly, but someone has to do the dirty job.
void NavParser::_fillEph(int nthLine, Ephemeris &eph, std::string &line) {
	switch(nthLine) {
	// First line.
	case 0:
	{ // Scope matters!!
		eph.PRN = std::stoi(line.substr(0, 2));

		// Calculate TOC.
		double tocy = std::stod(line.substr(2, 3));
		double tocm = std::stod(line.substr(5, 3));
		double tocd = std::stod(line.substr(8, 3));
		double toch = std::stod(line.substr(11, 3));
		double tocmin = std::stod(line.substr(14, 3));
		double tocs = std::stod(line.substr(17, 5));
		eph.toc = Utility::secondsFromGPSBegin(tocy, tocm, tocd, toch, tocmin, tocs);

		std::string _af0 = line.substr(22, 19);
		std::string _af1 = line.substr(41, 19);
		std::string _af2 = line.substr(60, 19);
		eph.af0 = Utility::fortranD2cppD(_af0);
		eph.af1 = Utility::fortranD2cppD(_af1);
		eph.af2 = Utility::fortranD2cppD(_af2);
		break;
	}
	case 1:
	{
		std::string _crs = line.substr(22, 19);
		std::string _deltaN = line.substr(41, 19);
		std::string _M0 = line.substr(60, 19);
		eph.crs = Utility::fortranD2cppD(_crs);
		eph.deltaN = Utility::fortranD2cppD(_deltaN);
		eph.M0 = Utility::fortranD2cppD(_M0);
		break;
	}
	case 2:
	{
		std::string _cuc = line.substr(3, 19);
		std::string _e = line.substr(22, 19);
		std::string _cus = line.substr(41, 19);		
		std::string _sqrtA = line.substr(60, 19);
		eph.cuc = Utility::fortranD2cppD(_cuc);
		eph.e = Utility::fortranD2cppD(_e);
		eph.cus = Utility::fortranD2cppD(_cus);
		eph.sqrtA = Utility::fortranD2cppD(_sqrtA);
		break;
	}
	case 3:
	{
		std::string _toe = line.substr(3, 19);
		std::string _cic = line.substr(22, 19);
		std::string _omega0 = line.substr(41, 19);
		std::string _cis = line.substr(60, 19);
		eph.toe = Utility::fortranD2cppD(_toe);
		eph.cic = Utility::fortranD2cppD(_cic);
		eph.omega0 = Utility::fortranD2cppD(_omega0);
		eph.cis = Utility::fortranD2cppD(_cis);
		break;
	}
	case 4:
	{
		std::string _i0 = line.substr(3, 19);
		std::string _crc = line.substr(22, 19);
		std::string _omega = line.substr(41, 19);
		std::string _omegaDot = line.substr(60, 19);
		eph.i0 = Utility::fortranD2cppD(_i0);
		eph.crc = Utility::fortranD2cppD(_crc);
		eph.omega = Utility::fortranD2cppD(_omega);
		eph.omegaDot = Utility::fortranD2cppD(_omegaDot);
		break;
	}
	case 5:
	{
		std::string _idot = line.substr(3, 19);
		std::string _week = line.substr(41, 19);
		eph.idot = Utility::fortranD2cppD(_idot);
		eph.week = Utility::fortranD2cppD(_week);
		break;
	}
	default:
		break;
	}
}
