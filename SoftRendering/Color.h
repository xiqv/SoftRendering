#ifndef COLOR_H
#define COLOR_H

#include "Xmath.h"

class Color {
public:
	float r;
	float g;
	float b;
	float a;

	explicit Color(uint32_t rgba);
	Color(float _r = 1.0f, float _g = 1.0f, float _b = 1.0f, float _a = 1.0f) :r(_r), g(_g), b(_b), a(_a) { }

	Color operator+(const Color& c) const {
		float addR = XMATH::min(r + c.r, 1.0f);
		float addG = XMATH::min(g + c.g, 1.0f);
		float addB = XMATH::min(b + c.b, 1.0f);
		float addA = XMATH::min(a + c.a, 1.0f);

		return Color(addR, addG, addB, addA);
	}

	Color operator-(const Color& c) const {
		return Color(r - c.r, g - c.g, b - c.b, a - c.a);
	}

	Color operator*(float factor) const {
		return Color(r*factor, g*factor, b*factor, a*factor);
	}

	Color operator*(const Color& c) const {
		return Color(r * c.r, g * c.g, b * c.b, a);
	}

	Color interpolate(const Color& c, float factor) const {
		return *this + (c - *this) * factor;
	}

	uint32_t getUint32() const;
};

inline
Color operator*(float factor, const Color& c) {
	return c * factor;
}

inline
Color::Color(uint32_t rgba) {
	r = ((rgba & 0xff000000) >> 24) / 255.0f;
	g = ((rgba & 0x00ff0000) >> 16) / 255.0f;
	b = ((rgba & 0x0000ff00) >> 8) / 255.0f;
	a = (rgba & 0x000000ff) / 255.0f;
}

inline 
uint32_t Color::getUint32() const {
	uint32_t R = uint32_t(r * 255);
	uint32_t G = uint32_t(g * 255);
	uint32_t B = uint32_t(b * 255);
	uint32_t A = uint32_t(a * 255);

	uint32_t value = (R << 24) | (G << 16) | (B << 8) | A;   //这里与萧大的不同
	return value;
}

#endif