/*
*	Gabriela Aguilar Lugo			A01373890
*	Gráficas Computacionales
*	Prof. Oriam De Gyves
*/

#include "Transform.h"

Transform::Transform()
{
	_position = glm::vec3(0.0f, 0.0f, 0.0f);
	_rotation = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f));
	_scale = glm::vec3(1.0f, 1.0f, 1.0f);

	_modelMatrix = glm::mat4(1.0f);

	_forward = WORLD_FORWARD_VECTOR;
	_up = WORLD_UP_VECTOR;
	_right = WORLD_RIGHT_VECTOR;
}

glm::mat4 Transform::GetModelMatrix()
{
	return _modelMatrix;
}

glm::vec3 Transform::GetPosition()
{
	return _position;
}

glm::quat Transform::GetRotation()
{
	return _rotation;
}

glm::vec3 Transform::GetScale()
{
	return _scale;
}

void Transform::SetPosition(float x, float y, float z)
{
	_position = glm::vec3(x, y, z);
	UpdateModelMatrixPosition();
}

void Transform::SetRotation(float x, float y, float z)
{
	_rotation = glm::quat(glm::radians(glm::vec3(x, y, z)));
	UpdateModelMatrixRotationScale();
}

void Transform::SetScale(float x, float y, float z)
{
	_scale = glm::vec3(x, y, z);
	UpdateModelMatrixRotationScale();
}

void Transform::MoveForward(float delta, bool world)
{
	if (world)
		_position += WORLD_FORWARD_VECTOR * delta;
	else
		_position += _forward * delta;

	UpdateModelMatrixPosition();
}

void Transform::MoveUp(float delta, bool world)
{
	if (world)
		_position += WORLD_UP_VECTOR * delta;
	else
		_position += _up * delta;

	UpdateModelMatrixPosition();
}

void Transform::MoveRight(float delta, bool world)
{
	if (world)
		_position += WORLD_RIGHT_VECTOR * delta;
	else
		_position += _right * delta;

	UpdateModelMatrixPosition();
}

void Transform::Translate(float x, float y, float z, bool world)
{
	if (world)
		_position += glm::vec3(x, y, z);
	else
	{
		_position += _forward * z;
		_position += _up * y;
		_position += _right * x;
	}
	UpdateModelMatrixPosition();
}

void Transform::Rotate(float x, float y, float z, bool world)
{
	glm::quat newRotation = glm::quat(glm::radians(glm::vec3(x, y, z)));

	if (world)
		_rotation = newRotation * _rotation;
	else
		_rotation = _rotation * newRotation;
	UpdateModelMatrixRotationScale();
}

void Transform::UpdateModelMatrixPosition()
{
	_modelMatrix[3][0] = _position.x;
	_modelMatrix[3][1] = _position.y;
	_modelMatrix[3][2] = _position.z;
}

void Transform::UpdateModelMatrixRotationScale()
{
	_modelMatrix = glm::mat4_cast(_rotation);
	_modelMatrix[0] = _modelMatrix[0] * _scale.x;
	_modelMatrix[1] = _modelMatrix[1] * _scale.y;
	_modelMatrix[2] = _modelMatrix[2] * _scale.z;
	UpdateModelMatrixPosition();
	UpdateLocalVectors();
}

void Transform::UpdateLocalVectors()
{
	glm::mat4 rotationMatrix = glm::mat4_cast(_rotation);
	_forward = glm::vec3(rotationMatrix * glm::vec4(WORLD_FORWARD_VECTOR, 0.0f));
	_up = glm::vec3(rotationMatrix * glm::vec4(WORLD_UP_VECTOR, 0.0f));
	_right = glm::cross(_up, _forward);
}
