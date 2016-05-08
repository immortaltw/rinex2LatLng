#include <armadillo>
#include "ObsParser.h"
#include "NavParser.h"
#include "util.h"

using namespace arma;

int main() {
	std::cout << "main function" << std::endl;

	NavParser nParser(std::string("../../resources/brdc0760.16n"));
	nParser.parse();

	ObsParser oParser(std::string("../../resources/farb0760.16o"));
	oParser.parse();

	std::cout << "Parsing o and n files done." << std::endl;
	std::cout << "Calculating the location of first 5 observations." << std::endl;

	std::vector<ObsVars> obs = oParser.getObs();
	std::vector<double> approxPos = oParser.getApproxXYZ();

	const double speedOfLight = 299792458;

	mat rPos(4, 1);
	mat X(4, 1);
	X.fill(0.0);

	// Comupte locations from the first 5 observations of the o file.
	for (int i=0; i<5; ++i) {
		ObsVars _curObs = obs[i];
		int numOfSV = _curObs.PRNS.size();
		mat G(numOfSV, 4);
		mat rhoC(numOfSV, 1);

		rPos(0, 0) = approxPos[0];
		rPos(1, 0) = approxPos[1];
		rPos(2, 0) = approxPos[2];
		rPos(3, 0) = 0.0;

		// Naively run 10 iterations.
		int iter = 10;
		while (iter--) {

			for (int j=0; j<numOfSV; ++j) {
				Ephemeris eph = nParser.getEphemeris(_curObs.timeOfEpoch, _curObs.PRNS[j]);

				// 0. Push PR into rhoC vector.
				rhoC(j, 0) = _curObs.PRMap[_curObs.PRNS[j]];

				// 1. Remove SV clock bias/drift.
				// 1.1 Get SV time at transmission start.
				double SVTime = _curObs.timeOfEpoch - _curObs.PRMap[_curObs.PRNS[j]]/speedOfLight;
				double dt = SVTime-eph.toc;
				double tCorr = eph.af0 + (eph.af1 + eph.af2*dt)*dt;
				SVTime = SVTime-tCorr;

				// 2. Compute SV position in ECEF.
				SatPos sPos = Utility::computeSatPos(SVTime, eph);

				// 3. Get rho0
				double rho0 = sqrt(pow(sPos.x-rPos(0, 0), 2) +
							  	   pow(sPos.y-rPos(1, 0), 2) +
							  	   pow(sPos.z-rPos(2, 0), 2));

				// 3.1. Get rotated ECEF correction against rho0 due to 
				// 	    earth rotation during signal travel time.
				// 4. Get tropo correction.
				// 5. Get iono correction.

				// 6. Get corrected pseudo range.
				rhoC(j, 0) = rhoC(j, 0)+speedOfLight*tCorr-rho0;

				// 7. Generate the 'G' matrix.
				G(j, 0) = -((sPos.x - rPos(0, 0))/rho0);
				G(j, 1) = -((sPos.y - rPos(1, 0))/rho0);
				G(j, 2) = -((sPos.z - rPos(2, 0))/rho0);
				G(j, 3) = 1;
			}

			// Least square
			// X = inv(G'*G)*G'*rhoC
			X = inv(G.t()*G)*G.t()*rhoC;
			rPos = rPos + X;
		}

		std::cout.precision(11);
		std::cout << rPos(0, 0) << " " << rPos(1, 0) << " " << rPos(2, 0) << std::endl;
	}
}