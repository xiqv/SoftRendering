#include "Image.h"

#include "SRutility.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

Image::Image(const char * path) {
	std::ifstream imageIs(path);
	if (!imageIs) {
		fprintf(stderr, "Loading image fail.\n");
		return;
	}

	std::string line;

	getNextLine(imageIs, line);
	auto vs = splitLine(line);
	width = std::stoi(vs[1]);

	getNextLine(imageIs, line);
	vs = splitLine(line);
	height = std::stoi(vs[1]);

	image = new uint32_t[width*height];

	for (int i = 0; i != height; ++i) {
		getNextLine(imageIs, line);
		vs = splitLine(line);
		for (int j = 0; j != width; ++j) {
			std::istringstream iss(vs[j]);
			uint32_t value;
			iss >> value;
			image[i*width + j] = value;
		}
	}
	
}

void Image::saveImage(const char* name) const {
	if (width*height == 0) {
		//Œ¥∑÷≈‰ø’º‰
		fprintf(stderr, "This is a empty image.\n");
		return;
	}

	char fileName[sizeof(name) + 8];
	strcpy_s(fileName, name);
	strcat_s(fileName, ".xiimage");

	std::ofstream ofs(fileName);
	if (!ofs) {
		fprintf(stderr, "OUTPUT IMAGE FAILED.\n");
		return;
	}

	ofs << "Width: " << width << std::endl;
	ofs << "Height: " << height << std::endl;

	for (int i = 0; i != height; ++i) {
		for (int j = 0; j != width; ++j) {
			ofs << image[i*width + j] << " ";
		}
		ofs << "\n";
	}

	ofs.close();
}