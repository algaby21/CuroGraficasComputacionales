/*
*	Gabriela Aguilar Lugo			A01373890
*	Gráficas Computacionales
*	Prof. Oriam De Gyves
*/

#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <memory>

#include "Shader.h"

class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();

	void CreateProgram();
	void AttachShader(std::string name, GLenum type);
	void LinkProgram();

	void Activate();
	void Deactivate();

	void SetAttribute(GLuint locationIndex, std::string name);
	void SetUniformf(std::string name, float value);
	void SetUniformf(std::string name, float x, float y);
	void SetUniformf(std::string name, float x, float y, float z);
	void SetUniformf(std::string name, float x, float y, float z, float w);
	void SetUniformMatrix(std::string name, glm::mat4 matrix);

private:
	void DeleteAndDetachShaders();
	void DeleteProgram();

	GLuint _programHandle;
	std::vector<std::unique_ptr<Shader>> _attachedShaders;
};
