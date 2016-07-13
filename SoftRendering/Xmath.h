#ifndef  XMATH_H
#define XMATH_H

#include <cmath>

namespace XMATH {
	const float PI = 3.141592654f;
	const float PI2 = 6.283185307f;
	const float EpsilonE4 = float(1E-4);

	static inline
	bool equal(float a, float b) {
		if (fabsf(a - b) < EpsilonE4) {
			return true;
		}
		return false;
	}

	static inline
	float min(float a, float b) {
		return a < b ? a : b;
	}

	static inline
	float max(float a, float b) {
		return a < b ? b : a;
	}

	static inline
	float radiansFromDegrees(float degrees) {
		return PI * degrees / 180.0f;
	}

	static inline
	float degreesFromRadians(float radians) {
		return radians*180.0f / PI;
	}

};

#endif