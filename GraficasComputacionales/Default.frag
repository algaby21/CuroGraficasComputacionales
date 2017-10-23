#version 330

in vec3 InterpolatedColor;

out vec4 FragColor;

void main()
{
	FragColor = vec4(InterpolatedColor, 1.0f);
}
