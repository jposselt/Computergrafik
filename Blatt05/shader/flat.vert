#version 330 core

in vec3 position;
in vec3 color;
in vec3 normal;

uniform mat4 mvp;   // model-view-projection
uniform mat4 model; // model
uniform mat3 nm;    // normal matrix
uniform vec4 lightPosition;
uniform vec3 material;

flat out vec3 fragmentColor;

void main()
{
	vec3 surfaceToLight;

	vec3 surfacePos = vec3(model * vec4(position, 1));

	// check if this is a directional light
	if(lightPosition.w == 0.0) {
		//directional light
		surfaceToLight = normalize(lightPosition.xyz);
	} else {
		// NOT a directional light
		surfaceToLight = normalize(lightPosition.xyz - surfacePos);
	}

	vec3 n = normalize(nm * normal);
	float fDiff = max(0.0, dot(n, surfaceToLight));
	fragmentColor = color * fDiff;

	gl_Position   = mvp * vec4(position,  1.0);
}