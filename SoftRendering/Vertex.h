#ifndef VERTEX_H
#define VERTEX_H

#include "Vector3.h"
#include "Color.h"

class Vertex {
public:
	XMATH::Vector3 position;

	//纹理采样坐标
	float u = 0;
	float v = 0;

	XMATH::Vector3 normal;
	Color color;

	Vertex(const XMATH::Vector3& _postion, 
		   float _u = 0.0f, float _v = 0.0f, 
		   const XMATH::Vector3& _normal = XMATH::Vector3(), 
		   const Color& _color = Color()) :
		position(_postion), u(_u), v(_v), normal(_normal), color(_color) { }
	
	Vertex interpolate(const Vertex& vertex, float factor) const {
		return Vertex(position.interpolate(vertex.position, factor),
			u + (vertex.u - u)*factor,
			v + (vertex.v - v)*factor,
			normal.interpolate(vertex.normal, factor),
			color.interpolate(vertex.color, factor));
	}
};

#endif