#ifndef MATRIX4X4_H
#define MATRIX4X4_H

#include <cmath>

#include "Vector3.h"
#include "Xmath.h"

namespace XMATH {
	class Matrix4x4 {
	public:
		float mat[16];

		Matrix4x4() {
			for (int i = 0; i != 16; ++i) {
				mat[i] = 0;
			}
		}

		Matrix4x4(float mat_[]) {
			int sz = sizeof(mat_) / sizeof(float);
			
			if (sz >= 16) {
				for (int i = 0; i != 16; ++i) {
					mat[i] = mat_[i];
				}
			}
			else {
				for (int i = 0; i != sz; ++i) {
					mat[i] = mat_[i];
				}
				for (int i = sz; i != 16; ++i) {
					mat[i] = 0.0f;
				}
			}
		}//Matrix4x4(float mat_[])

		bool operator==(const Matrix4x4& m) const {
			for (int i = 0; i != 16; ++i) {
				if (!equal(mat[i],m.mat[i])) {
					return false;
				}
			}
			return true;
		}

		static Matrix4x4 identity() {
			float retMat[] = {
				1,0,0,0,
				0,1,0,0,
				0,0,1,0,
				0,0,0,1
			};
			return Matrix4x4(retMat);
		}

		static Matrix4x4 rotationX(float angle) {
			float s = sinf(angle);
			float c = cosf(angle);

			float retMat[] = {
				1, 0, 0, 0,
				0, c, s, 0,
				0,-s,-c, 0,
				0, 0, 0, 1
			};
			return Matrix4x4(retMat);
		}

		static Matrix4x4 rotationY(float angle) {
			float s = sinf(angle);
			float c = cosf(angle);

			float retMat[] = {
				c, 0,-s, 0,
				0, 1, 0, 0,
				s, 0, c, 0,
				0, 0, 0, 1
			};
			return Matrix4x4(retMat);
		}

		static Matrix4x4 rotationZ(float angle) {
			float s = sinf(angle);
			float c = cosf(angle);

			float retMat[] = {
				c, s, 0, 0,
			   -s, c, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1
			};
			return Matrix4x4(retMat);
		}

		static Matrix4x4 rotation(const Vector3& r) {
			Matrix4x4 x = rotationX(r.x);
			Matrix4x4 y = rotationX(r.y);
			Matrix4x4 z = rotationX(r.z);

			return x * y * z;
		}

		static Matrix4x4 scale(const Vector3& s) {
			float retMat[]{
				s.x, 0,   0,  0,
				0,   s.y, 0,  0,
				0,   0,   s.z,0,
				0,   0,   0,  1
			};
			return Matrix4x4(retMat);
		}

		Matrix4x4 translation(const Vector3& v) const {
			float retMat[] = {
				1,   0,   0,  0,
				0,   1,   0,  0,
				0,   0,   1,  0,
				v.x, v.y, v.z,  1
			};
			return Matrix4x4(retMat);
		}

		Vector3 transform(const Vector3& v) const {
			float x = v.x * mat[4 * 0] + v.y*mat[4 * 1] + v.z*mat[4 * 2] + mat[4 * 3];
			float y = v.x * mat[4 * 0 + 1] + v.y*mat[4 * 1 + 1] + v.z*mat[4 * 2 + 1] + mat[4 * 3 + 1];
			float z = v.x * mat[4 * 0 + 2] + v.y*mat[4 * 1 + 2] + v.z*mat[4 * 2 + 2] + mat[4 * 3 + 2];
			float w = v.x * mat[4 * 0 + 3] + v.y*mat[4 * 1 + 3] + v.z*mat[4 * 2 + 3] + mat[4 * 3 + 3];

			float reciprocalW = 1 / w;
			return Vector3(x * reciprocalW, y * reciprocalW, z * reciprocalW);
		}

		Matrix4x4 operator*(const Matrix4x4& m) const {
			Matrix4x4 retMat;
			for (int i = 0; i != 16; ++i) {
				int j = i / 4 * 4;
				int k = i % 4;

				float value = mat[j] * m.mat[k] + mat[j + 1] * m.mat[k + 4] + 
							  mat[j + 2] * m.mat[k + 2 * 4] + mat[j + 3] * m.mat[k + 3 * 4];
				retMat.mat[i] = value;
			}
		}
	};

	Vector3 operator*(const Vector3& v,const Matrix4x4& m) {
		return m.transform(v);
	}
};

#endif