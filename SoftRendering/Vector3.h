#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>

#include "Xmath.h"

namespace XMATH {
	class Vector3 {
		//1X3 Vector
	public:
		float x;
		float y;
		float z;

		Vector3(float x_ = 0.0f, float y_ = 0.0f, float z_ = 0.0f) :x(x_), y(y_), z(z_) { }

		float length() const;
		Vector3 normalize() const;
		float dot(const Vector3& v) const;
		Vector3 cross(const Vector3& v) const;
		Vector3 interpolate(const Vector3 &v, float factor) const;

		Vector3 operator+(const Vector3& v) const;
		Vector3 operator-(const Vector3& v) const;
		Vector3 operator*(float factor) const;
		bool operator==(const Vector3& v) const;
	};

	inline
	Vector3 operator*(float factor, const Vector3& v) {
		return v * factor;
	}

	inline
	float Vector3::length() const {
		return sqrtf(x*x + y*y + z*z);
	}

	inline
	Vector3 Vector3::normalize() const {
		float len = length();
		if (equal(len,0.0f)) {
			return Vector3();
		}
		float reciprocalLen = 1 / len;
		return Vector3(x *reciprocalLen, y *reciprocalLen, z *reciprocalLen);
	}

	inline 
	float Vector3::dot(const Vector3 & v) const {
		return x*v.x + y*v.y + z*v.z;
	}

	inline 
	Vector3 Vector3::cross(const Vector3 & v) const {
		float retX = y*v.z - z*v.y;
		float retY = z*v.x - x * v.z;
		float retZ = z*v.y - y*v.x;
		return Vector3(retX, retY, retZ);
	}

	inline 
	Vector3 Vector3::interpolate(const Vector3 & v, float factor) const {
		return *this + factor * (v - *this);
	}

	inline 
	Vector3 Vector3::operator+(const Vector3 & v) const {
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	inline 
	Vector3 Vector3::operator-(const Vector3 & v) const {
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	inline 
	Vector3 Vector3::operator*(float factor) const {
		return Vector3(factor*x, factor*y, factor*z);
	}

	inline 
	bool Vector3::operator==(const Vector3 & v) const {
		return equal(x,v.x) && equal(y,v.y) && equal(z,v.z);
	}
};

#endif