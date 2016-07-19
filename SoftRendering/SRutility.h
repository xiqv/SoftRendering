#ifndef SRUTILITY_H
#define SRUTILITY_H

#include <fstream>
#include <string>
#include <vector>
#include <sstream>

void getNextLine(std::istream & is, std::string & line);

std::vector<std::string> splitLine(const std::string & s);

#endif