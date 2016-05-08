#include <iostream>
#include <cmath>
#include <ctime>

#include "util.h"

double Utility::fortranD2cppD(std::string &fortranD) {
	std::size_t pos = fortranD.find("D");
	std::string digits = fortranD.substr(0, pos);
	std::string sign = fortranD.substr(pos+1, 1);
	std::string factor = fortranD.substr(pos+2);

	// Great!! c++ already provides us a nice little string to double tool!
	double res = std::stod(digits);
	double factorD = pow(10, std::stod(factor)); // Overflow?

	// minus sign: divide.
	if (sign == "-") {
		// And string to interger!!! Nice!!!
		res /= factorD;
	}
	// plus sign: multiply. 
	else {
		// Overflow?
		res *= factorD;
	}
	return res;
}

// Not very robust.
double Utility::secondsFromGPSBegin(double y, double m, double d,
									  double h, double min, double s) {
	struct tm tGPS = {0};
	struct tm tN = {0};
	// Zero time-point of GPS is defined as 12:00am of 1/6/1980.
	tGPS.tm_year = 80;
	tGPS.tm_mon = 0;
	tGPS.tm_mday = 6;
	tGPS.tm_hour = 0;
	tGPS.tm_min = 0;
	tGPS.tm_sec = 0;

	tN.tm_year = y<80? y+100: y;
	tN.tm_mon = m;
	tN.tm_mday = d;
	tN.tm_hour = h;
	tN.tm_min = min;
	tN.tm_sec = s;

	return difftime(mktime(&tN), mktime(&tGPS));
}

// Ref: http://kom.aau.dk/~borre/easy/satpos.m
SatPos Utility::computeSatPos(double SVTime, Ephemeris &eph) {
	SatPos ret;

	double GM = 3.986005e14;             // earth's universal gravitational param, m^3/s^2
	double Omegae_dot = 7.2921151467e-5; // earth rotation rate, rad/s

	double weekNo = eph.week;
	SVTime = fmod(SVTime, 604800);
	double A = eph.sqrtA*eph.sqrtA;
	double tk = SVTime-eph.toe;
	double n0 = sqrt(GM/pow(A, 3.0));
	double n = n0 + eph.deltaN;
	double M = fmod((eph.M0+n*tk)+2*M_PI, 2*M_PI);
	double E = M;

	for (int i=0; i<10; ++i) {
	   double E_old = E;
	   E = M+eph.e*sin(E);
	   double dE = fmod(E-E_old, 2*M_PI);
	   if (std::abs(dE) < 1.e-12) break;
	}

	E = fmod(E+2*M_PI, 2*M_PI);

	double v = atan2(sqrt(1-pow(eph.e, 2.0))*sin(E), cos(E)-eph.e);
	double phi = fmod(v+eph.omega, 2*M_PI);
	double u = phi				  + eph.cuc*cos(2*phi) + eph.cus*sin(2*phi);
	double r = A*(1-eph.e*cos(E)) + eph.crc*cos(2*phi) + eph.crs*sin(2*phi);
	double i = eph.i0+eph.idot*tk + eph.cic*cos(2*phi) + eph.cis*sin(2*phi);
	double Omega = eph.omega0+(eph.omegaDot-Omegae_dot)*tk-Omegae_dot*eph.toe;
	Omega = fmod(Omega+2*M_PI,2*M_PI);
	double x1 = cos(u)*r;
	double y1 = sin(u)*r;
	ret.x = x1*cos(Omega)-y1*cos(i)*sin(Omega);
	ret.y = x1*sin(Omega)+y1*cos(i)*cos(Omega);
	ret.z = y1*sin(i);	
	return ret;
}


// Ref: https://gist.github.com/klucar/1536194
std::vector<double> Utility::ecef2lla(SatPos &pos) {
	// WGS84 ellipsoid constants
	double a = 6378137; // radius
	double e = 8.1819190842622e-2;  // eccentricity

	double asq = pow(a,2);
	double esq = pow(e,2);

 	double b = sqrt( asq * (1-esq) );
 	double bsq = pow(b,2);
  	double ep = sqrt( (asq - bsq)/bsq);
  	double p = sqrt( pow(pos.x,2) + pow(pos.y,2) );
 	double th = atan2(a*pos.z, b*p);

 	double lon = atan2(pos.y, pos.x);
 	double lat = atan2( (pos.z + pow(ep,2)*b*pow(sin(th),3) ), (p - esq*a*pow(cos(th),3)) );
 	double N = a/( sqrt(1-esq*pow(sin(lat),2)) );
 	double alt = p / cos(lat) - N;

	// mod lat to 0-2pi
	lon = fmod(lon, 2*M_PI);

  	std::vector<double> ret = {lat, lon, alt};
 	return ret;
}
