#include "Canvas.h"

#include <cassert>

#include "Matrix4x4.h"
#include "Xmath.h"

using XMATH::Matrix4x4;

Vertex Canvas::project(const Vertex & v, const XMATH::Matrix4x4 & transform) const {
	XMATH::Vector3 transformPosition = transform.transform(v.position);

	transformPosition.x = (transformPosition.x + 1.0f)*_width*0.5f;  //这里不同
	transformPosition.y = (1.0f - transformPosition.y)*_height*0.5f;

	//transformPosition.x = transformPosition.x*_width+_width/2;  //这里不同
	//transformPosition.y = -transformPosition.y*_height + _height / 2;
	
	return Vertex(transformPosition, v.normal, v.u, v.v, v.color);
}

void Canvas::drawPixel(int x, int y, float z, const Color& c) {
	int index = y * _width + x;
	if (z > depthBuffer[index]) {
		return;
	}

	depthBuffer[index] = z;
	colorBuffer[index] = c.getUint32();
}

void Canvas::drawScanLine(const Vertex & v1, const Vertex & v2, const Texture & tex) {
	int x1 = int(v1.position.x);
	int x2 = int(v2.position.x);
	 
	int dx = x2 - x1;
	int sign = dx > 0 ? 1 : -1;
	float factor = 0.0f;

	for (int x = x1, i = 0; i != dx*sign + 1; ++i, x += sign){
		//利用i来控制循环,从而保证扫描线两端点均可被渲染
		if (dx != 0) {
			factor = float(x - x1) / dx;
		}
		
		Vertex v = v1.interpolate(v2, factor);

		Color colorV = tex.sample(v.u, v.v);

		drawPoint(XMATH::Vector3(v.position.x, v.position.y, v.position.z), colorV);
	}
}

void Canvas::drawPoint(const XMATH::Vector3& position, const Color& c) {
	if (position.x >= 0 && position.y >= 0 && position.x < _width&&position.y < _height) {
		drawPixel(int(position.x), int(position.y), position.z, c);
	}
}

void Canvas::drawLine(const Vertex & v1, const Vertex & v2) {
	int x1 = int(v1.position.x);
	int x2 = int(v2.position.x);
	int y1 = int(v1.position.y);
	int y2 = int(v2.position.y);

	int dx = x2 - x1;
	int dy = y2 - y1;

	if (std::abs(dx) > std::abs(dy)) {
		//比较平缓
		int sign = dx > 0 ? 1 : -1;

		float ratio = 0.0f;
		if (dx != 0) {
			ratio = 1.0f * dy / dx;
		}

		for (int x = x1; x != x2; x += sign) {
			int y = y1 + (x - x1)*ratio;
			Color colorXY = v1.color.interpolate(v2.color, float(x - x1) / dx);
			drawPoint(XMATH::Vector3(x, y), colorXY);
		}
	}//abs(dx) > abs(dy)
	else {
		int sign = dy > 0 ? 1 : -1;

		float ratio = 0.0f;
		if (dy != 0) {
			ratio = 1.0f * dx / dy;
		}

		for (int y = y1; y != y2; y += sign) {
			int x = x1 + (y - y1)*ratio;
			Color colorXY = v1.color.interpolate(v2.color, float(y - y1) / dy);
			drawPoint(XMATH::Vector3(x, y), colorXY);
		}
	}//Draw Line
}

void Canvas::drawTriangle(const Vertex & v1, const Vertex & v2, const Vertex & v3, const Texture & tex) {
	if (XMATH::equal(v1.position.y, v2.position.y) && XMATH::equal(v1.position.y, v3.position.y)) {
		//如果三点共线，则不绘制三角形
		return;
	}
	const Vertex *a = &v1;
	const Vertex *b = &v2;
	const Vertex *c = &v3;

	//sort a,b,c by y-value.
	//a->c ==> ymin->ymin  ==> top -> bottom 
	if (a->position.y > b->position.y) {
		std::swap(a, b);
	}
	if (b->position.y > c->position.y) {
		std::swap(b, c);
	}
	if (a->position.y > b->position.y) {
		std::swap(a, b);
	}

	float factorMid = (b->position.y - a->position.y) / (c->position.y - a->position.y);
	Vertex midVer = a->interpolate(*c, factorMid);

	int beginY = a->position.y;
	int endY = b->position.y;
	//Rasterize triangle AMB
	for (int y = beginY; y != endY + 1; ++y){
		float factor = 0.0f;
		if (endY - beginY != 0) {
			factor = float(y - beginY) / (endY - beginY);
		}

		Vertex factorAM = a->interpolate(midVer, factor);
		Vertex factorAB = a->interpolate(*b, factor);

		drawScanLine(factorAM, factorAB, tex);
	}

	//Rasterize triangle MBC
	beginY = b->position.y;
	endY = c->position.y;
	for (int y = beginY; y != endY + 1; ++y) {
		float factor = 0.0f;
		if (endY - beginY != 0) {
			factor = float(y - beginY) / (endY - beginY);
		}

		Vertex factorCM = midVer.interpolate(*c, factor);
		Vertex factorCB = b->interpolate(*c, factor);

		drawScanLine(factorCM, factorCB, tex);
	}
}

void Canvas::drawMesh(const Mesh & mesh) {
	Matrix4x4 scale = Matrix4x4::scale(mesh.scale);
	Matrix4x4 translation = Matrix4x4::translation(mesh.position);
	Matrix4x4 rotate = Matrix4x4::rotation(mesh.rotation);

	Matrix4x4 world = scale * rotate * translation;
	Matrix4x4 transform = world * _camera.cameraMatrix4x4();
	
	for (int i = 0; i != mesh.indices.size(); i+=3) {
		const Vertex &a = mesh.vertices[mesh.indices[i]];
		const Vertex &b = mesh.vertices[mesh.indices[i +1]];
		const Vertex &c = mesh.vertices[mesh.indices[i +2]];

		Vertex v1 = project(a, transform);
		Vertex v2 = project(b, transform);
		Vertex v3 = project(c, transform);

		drawTriangle(v1, v2, v3, *mesh.texture);
	}
}