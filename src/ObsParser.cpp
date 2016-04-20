#include <ifstream>
#include "ObsParser.h"

using namespace std;

void ObsParser::parse() {
	ifstream fin(_filePath, ios::in);
	string str;
	while(getline(fin, str)) {
		cout << str << endl;
	}
}