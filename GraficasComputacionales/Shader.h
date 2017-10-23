/*
*	Gabriela Aguilar Lugo			A01373890
*	Gráficas Computacionales
*	Prof. Oriam De Gyves
*/

#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include<iostream>

class Shader
{
public:
	Shader();
	~Shader();

	void CreateShader(std::string path, GLenum type);

	GLuint GetHandle();

private:
	GLuint _shaderHandle;
};
