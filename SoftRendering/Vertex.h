#ifndef VERTEX_H
#define VERTEX_H

#include "Vector3.h"
#include "Color.h"

class Vertex {
public:
	XMATH::Vector3 position;
	XMATH::Vector3 normal;

	//�����������
	float u = 0;
	float v = 0;

	Color color;

	Vertex(const XMATH::Vector3& _postion, 
		   const XMATH::Vector3& _normal = XMATH::Vector3(), 
		   float _u = 0.0f, float _v = 0.0f, 
		   const Color& _color = Color()) :
		position(_postion), normal(_normal), u(_u), v(_v), color(_color) { }
	
	Vertex interpolate(const Vertex& vertex, float factor) const {
		return Vertex(position.interpolate(vertex.position, factor),
			normal.interpolate(vertex.normal, factor),
			u + (vertex.u - u)*factor,
			v + (vertex.v - v)*factor,
			color.interpolate(vertex.color, factor));
	}
};

#endif