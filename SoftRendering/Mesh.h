#ifndef MESH_H
#define MESH_H

#include <fstream>
#include <string>
#include <vector>

#include "Vertex.h"

class Mesh {
public:
	XMATH::Vector3 position;
	XMATH::Vector3 rotation;
	XMATH::Vector3 scale;

	std::vector<Vertex> vertices;
	std::vector<unsigned> indices;

	//默认构造函数，自己手动定义Mesh
	Mesh();
	
	//从xi3d文件中载入Mesh数据
	Mesh(const char* path);
};

inline
Mesh::Mesh() {
	position = XMATH::Vector3(0.0f, 0.0f, 0.0f);
	rotation = XMATH::Vector3(0.0f, 0.0f, 0.0f);
	scale = XMATH::Vector3(1.0f, 1.0f, 1.0f);
}

#endif