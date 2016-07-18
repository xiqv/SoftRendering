#include <iostream>
#include <algorithm>
#include <vector>

#include "Matrix4x4.h"
#include "Vector3.h"
#include "Xmath.h"
#include "Color.h"
#include "Vertex.h"
#include "Mesh.h"

int main() {
	Mesh mesh("model.xi3d");
	auto mat = XMATH::Matrix4x4::rotation(mesh.rotation)*XMATH::Matrix4x4::scale(mesh.scale)*XMATH::Matrix4x4::translation(mesh.position);
	
	return 0;
}