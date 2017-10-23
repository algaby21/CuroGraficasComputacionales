/*
*	Gabriela Aguilar Lugo			A01373890
*	Gráficas Computacionales
*	Prof. Oriam De Gyves
*/

#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera()
{
	SetPerspective(1.0f, 1000.0f, 60.0f, 1.0f);
	_viewMatrix = glm::inverse(_transform.GetModelMatrix());
}

glm::mat4 Camera::GetViewProjection()
{
	return _projectionMatrix * _viewMatrix;
}

glm::mat4 Camera::GetViewMatrix()
{
	return _viewMatrix;
}

glm::mat4 Camera::GetProjectionMatrix()
{
	return _projectionMatrix;
}

glm::vec3 Camera::GetPosition()
{
	return _transform.GetPosition();
}

void Camera::SetPosition(float x, float y, float z)
{
	_transform.SetPosition(x, y, z);
	_viewMatrix = glm::inverse(_transform.GetModelMatrix());
}

void Camera::SetRotation(float x, float y, float z)
{
	_transform.SetRotation(x, y, z);
	_viewMatrix = glm::inverse(_transform.GetModelMatrix());
}

void Camera::MoveForward(float delta, bool world)
{
	_transform.MoveForward(delta, world);
	_viewMatrix = glm::inverse(_transform.GetModelMatrix());
}

void Camera::MoveUp(float delta, bool world)
{
	_transform.MoveUp(delta, world);
	_viewMatrix = glm::inverse(_transform.GetModelMatrix());
}

void Camera::MoveRight(float delta, bool world)
{
	_transform.MoveRight(delta, world);
	_viewMatrix = glm::inverse(_transform.GetModelMatrix());
}

void Camera::Yaw(float degrees)
{
	_transform.Rotate(0.0f, degrees, 0.0f, false);
	_viewMatrix = glm::inverse(_transform.GetModelMatrix());
}

void Camera::Roll(float degrees)
{
	_transform.Rotate(0.0f, 0.0f, degrees, false);
	_viewMatrix = glm::inverse(_transform.GetModelMatrix());
}

void Camera::Pitch(float degrees)
{
	_transform.Rotate(degrees, 0.0f, 0.0f, false);
	_viewMatrix = glm::inverse(_transform.GetModelMatrix());
}

void Camera::Rotate(float x, float y, float z, bool world)
{
	_transform.Rotate(x, y, z, world);
	_viewMatrix = glm::inverse(_transform.GetModelMatrix());
}

void Camera::SetPerspective(float nearPlane, float farPlane, float fieldOfView, float aspectRatio)
{
	_projectionMatrix = glm::perspective(glm::radians(fieldOfView),
		aspectRatio, nearPlane, farPlane);
}

void Camera::SetOrthographic(float size, float aspectRatio)
{
	float xSize = aspectRatio * size;
	_projectionMatrix = glm::ortho(-xSize, xSize,
		-size, size,
		-size, size);
}
