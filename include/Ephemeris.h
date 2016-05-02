/**
 * Extract from navigation file.
 * Will be used to calculate SV position.
 */
struct Ephemeris {
	int PRN;
	double af0;  // SV clock bias
	double af1;  // SV clock drift
	double af2;  // SV clock drift rate
	double toe;  // Time of week
	double toc;  // Time of clock
	/** 
	 * Perturbation Params
	 */
	double crs;
	double crc;
	double cus;
	double cuc;
	double cis;
	double cic;
	double deltaN;
	double omegaDot;
	double idot;
	/** 
	 * Keplerian Params
	 */
	double M0;
	double sqrtA;
	double i0;
	double omega0;
	double omega;
	double e;
};