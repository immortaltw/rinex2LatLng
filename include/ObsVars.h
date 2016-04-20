#include <iostream>
#include <vector>
#include <string>

struct ObsVars {
	int interval;       // Observation Interval
	double x0;			// Approximate X location
	double y0;			// Approximate Y location
	double z0;			// Approximate Z location
	double startTime;   // Observation start time
	double currTime;    // Current observation time
	double pseudoRange; // Use L1 code phase pseudo range only
	std::vector<std::string> PRNS;  // PRN names
};