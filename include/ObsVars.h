#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

struct ObsVars {
	double timeOfEpoch;       // Time of epoch
	double _dt;	        // Receiver clock offset (sec)
	std::unordered_map<int, double> pseudorangeMap; // PRN # vs L1 C/A code pseudorange
	std::vector<int> PRNS;  // PRN #s (assume all GPS)
	void clear() {
		timeOfEpoch = 0.0;
		pseudorangeMap.clear();
		PRNS.clear();
	}
};