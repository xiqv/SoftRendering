#ifndef CANVAS_H
#define CANVAS_H

#include <stdint.h>

#include "Mesh.h"
#include "Color.h"
#include "Vertex.h"
#include "Camera.h"
#include "Vector3.h"
#include "Texture.h"

class Canvas {
public:
	Canvas(uint32_t *drawBuffer, int width, int height);

	void setCamera(const Camera& camera);

	void clear();
	void setClearColor(uint32_t c);
	void setClearColor(const Color& c);
	void setClearColor(float r = 0.0f, float g = 0.0f, float b = 0.0f);

	void drawPoint(const XMATH::Vector3& postion, const Color& c);
	void drawLine(const Vertex& v1, const Vertex& v2);
	void drawTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3,const Texture& tex);
	void drawMesh(const Mesh& mesh);

	~Canvas();
private:
	uint32_t *colorBuffer;
	float *depthBuffer;

	int _width;
	int _height;

	Color clearColor;

	Camera _camera;

	Vertex project(const Vertex& v, const XMATH::Matrix4x4& transform) const;
	void drawPixel(int x, int y, float z, const Color& c);
	void drawScanLine(const Vertex& v1, const Vertex& v2, const Texture& tex);
};

inline
Canvas::~Canvas() {
	delete[] depthBuffer;
}

inline
Canvas::Canvas(uint32_t * drawBuffer, int width, int height)
	: colorBuffer(drawBuffer), _width(width), _height(height) {
	clearColor = Color(0.0f,0.0f,0.0f);
	depthBuffer = new float[_width*_height];
}

inline 
void Canvas::setCamera(const Camera & camera) {
	_camera = camera;
}

inline
void Canvas::clear() {
	memset(colorBuffer, clearColor.getUint32(), _width*_height*sizeof(uint32_t));
	std::fill(depthBuffer, depthBuffer + _width*_height, FLT_MAX);
}

inline
void Canvas::setClearColor(uint32_t c) {
	clearColor = Color(c);
}

inline
void Canvas::setClearColor(const Color& c) {
	clearColor = c;
}

inline 
void Canvas::setClearColor(float r, float g, float b) {
	clearColor = Color(r, g, b);
}

#endif