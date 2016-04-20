/**
 * Extract from navigation file.
 * Will be used to calculate SV position.
 */
struct Ephemeris {
	int PRN;
	float af0;  // SV clock bias
	float af1;  // SV clock drift
	float af2;  // SV clock drift rate
	float toe;  // Time of week
	float toc;  // Time of clock
	/** 
	 * Perturbation Params
	 */
	float crs;
	float crc;
	float cus;
	float cuc;
	float cis;
	float cic;
	float deltaN;
	float omegaDot;
	float idot;
	/** 
	 * Keplerian Params
	 */
	float M0;
	float sqrtA;
	float i0;
	float omegaA;
	float omega;
	float e;
};