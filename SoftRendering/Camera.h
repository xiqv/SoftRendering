#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"
#include "Matrix4x4.h"

class Camera {
public:
	Camera() = default;

	Camera(const XMATH::Vector3& position, const XMATH::Vector3& target, const XMATH::Vector3 up) :
		_position(position), _target(target), _up(up) { }

	Camera(float fieldOfView, float aspect, float zNear, float zFar) :
		_fieldOfView(fieldOfView), _aspect(aspect), _zNear(zNear), _zFar(zFar) { }

	Camera(const XMATH::Vector3& position, const XMATH::Vector3& target, const XMATH::Vector3 up,
		float fieldOfView, float aspect, float zNear, float zFar) :
		_position(position), _target(target), _up(up),
		_fieldOfView(fieldOfView), _aspect(aspect), _zNear(zNear), _zFar(zFar) { }

	void setPerspective(float fieldOfView, float aspect, float zNear, float zFar);

	void updateCameraMatrix();
	XMATH::Matrix4x4 cameraMatrix4x4() const;

	XMATH::Vector3 _position;
	XMATH::Vector3 _target;
	XMATH::Vector3 _up;
private:
	float _fieldOfView = 0.0f;
	float _aspect = 0.0f;
	float _zNear = 0.0f;
	float _zFar = 0.0f;

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
XMATH::Matrix4x4 Camera::cameraMatrix4x4() const {
	return cameraMatrix;
}

inline 
void Camera::updateCameraMatrix() {
	cameraMatrix = XMATH::Matrix4x4::lookAt(_position, _target, _up) *
		XMATH::Matrix4x4::perspective(XMATH::radiansFromDegrees(_fieldOfView), _aspect, _zNear, _zFar);
}

#endif