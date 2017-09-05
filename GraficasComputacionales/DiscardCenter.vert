#version 330

in vec3 VertexPosition;
in vec3 VertexColor;

out vec3 InterpolatedColor;

void main()
{
	InterpolatedColor = VertexColor;
	gl_Position = vec4(VertexPosition, 1.0f);
}