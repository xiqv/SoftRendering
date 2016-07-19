#include "Mesh.h"

#include "SRutility.h"

#include <iostream>
#include <sstream>

using std::stof;
using std::stoi;

Mesh::Mesh(const char * path) {
	position = XMATH::Vector3(0.0f, 0.0f, 0.0f);
	rotation = XMATH::Vector3(0.0f, 0.0f, 0.0f);
	scale = XMATH::Vector3(1.0f, 1.0f, 1.0f);

	std::ifstream meshIs(path);
	if (!meshIs) {
		std::cerr << "Loading Mesh File Fail." << std::endl;
		return;
	}

	std::string line;

	getNextLine(meshIs, line);
	auto vs = splitLine(line);
	int sizeOfVertices = std::stoi(vs[1]);

	getNextLine(meshIs, line);
	vs = splitLine(line);
	int sizeOfTriangles = std::stoi(vs[1]);

	for (int i = 0; i != sizeOfVertices; ++i) {
		getNextLine(meshIs, line);
		vs = splitLine(line);

		float x = stof(vs[0]);
		float y = stof(vs[1]);
		float z = stof(vs[2]);

		float nx = stof(vs[3]);
		float ny = stof(vs[4]);
		float nz = stof(vs[5]);

		float u = stof(vs[6]);
		float v = stof(vs[7]);

		vertices.push_back(Vertex(XMATH::Vector3(x, y, z), XMATH::Vector3(nx, ny, nz), u, v, Color()));
	}

	for (int i = 0; i != sizeOfTriangles; ++i) {
		getNextLine(meshIs, line);
		vs = splitLine(line);
		
		indices.push_back(stoi(vs[0]));
		indices.push_back(stoi(vs[1]));
		indices.push_back(stoi(vs[2]));
	}
	meshIs.close();
}
