/*
*	Gabriela Aguilar Lugo			A01373890
*	Gráficas Computacionales
*	Prof. Oriam De Gyves
*/
#include "Mesh.h"
#include <iostream>

Mesh::Mesh()
{
	_vertexCount = 0;
	_vertexArrayObject = 0;
	_positionsVertexBufferObject = 0;
	_colorsVertexBufferObject = 0;
	_indice = 0; //_indicesCount=0;
	_indicesBuffer = 0; // _indicesbufferobject=0;
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &_vertexArrayObject);
	glDeleteBuffers(1, &_positionsVertexBufferObject);
	glDeleteBuffers(1, &_colorsVertexBufferObject);
	_vertexCount = 0;
}

void Mesh::CreateMesh(GLint vertexCount)
{
	glGenVertexArrays(1, &_vertexArrayObject);
	_vertexCount = vertexCount;
}

void Mesh::Draw(GLenum primitive)
{
	glBindVertexArray(_vertexArrayObject);
	if (_indice > 0) {
		glDrawElements(primitive, _indice, GL_UNSIGNED_INT, nullptr);

	}else {
		glDrawArrays(primitive, 0, _vertexCount);
	}


	glBindVertexArray(0);
}

void Mesh::SetPositionAttribute(std::vector<glm::vec2> positions, GLenum usage, GLuint locationIndex)
{
	if (positions.size() > 0 && positions.size() == _vertexCount)
		SetAttributeData(_positionsVertexBufferObject, sizeof(glm::vec2) * positions.size(), positions.data(), usage, locationIndex, 2);
}

void Mesh::SetPositionAttribute(std::vector<glm::vec3> positions, GLenum usage, GLuint locationIndex)
{
	if (positions.size() > 0 && positions.size() == _vertexCount)
		SetAttributeData(_positionsVertexBufferObject, sizeof(glm::vec3) * positions.size(), positions.data(), usage, locationIndex, 3);
}

void Mesh::SetColorAttribute(std::vector<glm::vec3> colors, GLenum usage, GLuint locationIndex)
{
	if (colors.size() > 0 && colors.size() == _vertexCount)
		SetAttributeData(_colorsVertexBufferObject, sizeof(glm::vec3) * colors.size(), colors.data(), usage, locationIndex, 3);
}

void Mesh::SetColorAttribute(std::vector<glm::vec4> colors, GLenum usage, GLuint locationIndex)
{
	if (colors.size() > 0 && colors.size() == _vertexCount)
		SetAttributeData(_colorsVertexBufferObject, sizeof(glm::vec4) * colors.size(), colors.data(), usage, locationIndex, 4);
}

void Mesh::SetAttributeData(GLuint& buffer, const GLsizeiptr size, const void* data, GLenum usage, GLuint locationIndex, const GLint components)
{

	if (buffer)
		glDeleteBuffers(1, &buffer);

	glBindVertexArray(_vertexArrayObject);

	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);
	glEnableVertexAttribArray(locationIndex);
	glVertexAttribPointer(locationIndex, components, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void Mesh::SetIndices(std::vector<unsigned int> index, GLenum usage) {

	if (index.size() > 0) {
		_indice = index.size();
		}
	glBindVertexArray(_vertexArrayObject);
	glGenBuffers(1, &_indicesBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indicesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * index.size(), index.data(), usage);
	glBindVertexArray(0);


}
