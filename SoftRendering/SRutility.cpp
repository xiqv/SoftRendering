#include "SRutility.h"

void getNextLine(std::istream & is, std::string & line) {
	//Get next line from the input stream is and save it into line.
	while (true) {
		std::getline(is, line);
		if (!line.empty() && line[0] != '#') {
			break;
		}
	}
}

std::vector<std::string> splitLine(const std::string & s) {
	//Split the string s to vector<string> by space.
	std::vector<std::string> vs;
	std::istringstream iss(s);

	std::string splitS;
	while (!iss.eof()) {
		iss >> splitS;
		vs.push_back(splitS);
	}
	return vs;
}