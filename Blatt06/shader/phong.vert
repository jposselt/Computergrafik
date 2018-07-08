#version 330 core

in vec3 position;
in vec3 color;
in vec3 normal;
in vec2 texCoord;

uniform mat4 mvp;   // model-view-projection
uniform mat4 model; // model
uniform mat3 nm;    // normal matrix

out vec3 outColor;
smooth out vec3 n;
smooth out vec3 surfacePos;
out vec2 fragTexCoord;

void main()
{
	n = normalize(nm * normal);
	surfacePos = vec3(model * vec4(position, 1));
	outColor = color;
	fragTexCoord = texCoord;
	gl_Position   = mvp * vec4(position,  1.0);
}