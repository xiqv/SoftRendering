#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"
#include "Matrix4x4.h"

class Camera {
public:
	Camera() {
		updateCameraMatrix();
	}

	Camera(const XMATH::Vector3& _position, const XMATH::Vector3& _target, const XMATH::Vector3 _up) :
		position(_position), target(_target), up(_up) {
		updateCameraMatrix();
	}

	Camera(float fieldOfViewDegree, float aspect, float zNear, float zFar) :
		_fieldOfView(fieldOfViewDegree), _aspect(aspect), _zNear(zNear), _zFar(zFar) {
		updateCameraMatrix();
	}

	Camera(const XMATH::Vector3& _position, const XMATH::Vector3& _target, const XMATH::Vector3 _up,
		float fieldOfViewDegree, float aspect, float zNear, float zFar) :
		position(_position), target(_target), up(_up),
		_fieldOfView(fieldOfViewDegree), _aspect(aspect), _zNear(zNear), _zFar(zFar) {
		updateCameraMatrix();
	}

	void setPerspective(float fieldOfViewDegree, float aspect, float zNear, float zFar);

	void updateCameraMatrix();
	const XMATH::Matrix4x4& cameraMatrix4x4() const;

	XMATH::Vector3 position;
	XMATH::Vector3 target;
	XMATH::Vector3 up;
private:
	float _fieldOfView = 45.0f;
	float _aspect = 1.0f;
	float _zNear = 0.1f;
	float _zFar = 1.0f;

	XMATH::Matrix4x4 cameraMatrix;
};

inline 
void Camera::setPerspective(float fieldOfViewDegree, float aspect, float zNear, float zFar) {
	_fieldOfView = fieldOfViewDegree;
	_aspect = aspect;
	_zNear = zNear;
	_zFar = zFar;
}

inline
const XMATH::Matrix4x4& Camera::cameraMatrix4x4() const {
	return cameraMatrix;
}

inline 
void Camera::updateCameraMatrix() {
	cameraMatrix = XMATH::Matrix4x4::lookAt(position, target, up) *
		XMATH::Matrix4x4::perspective(XMATH::radiansFromDegrees(_fieldOfView), _aspect, _zNear, _zFar);
}

#endif