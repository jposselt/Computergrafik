#version 330 core

in vec3 position;
in vec3 color;

uniform mat4 mvp;
uniform bool useTexture;

out vec3 fragmentColor;

void main()
{
	if(!useTexture) {
		fragmentColor = color;
		gl_Position   = mvp * vec4(position,  1.0);
	}
}