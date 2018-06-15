#version 330 core

in vec3 position;
in vec3 color;
in vec3 normal;

uniform mat4 mvp;  // model-view-projection
uniform mat3 nm;   // normal matrix
uniform vec3 lightDirection;
uniform vec3 material;

flat          out vec3 fragmentColor;

void main()
{
	vec3  n     = normalize(nm * normal);
	float fDiff = max(0.0, dot(n, lightDirection));

        fragmentColor = color * fDiff;
	gl_Position   = mvp * vec4(position,  1.0);
}