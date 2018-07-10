#version 330 core

in vec3 position;
in vec3 color;
in vec3 normal;
in vec2 texCoord;

uniform mat4 mvp;   // model-view-projection
uniform mat4 model; // model
uniform mat3 nm;    // normal matrix

uniform vec4 lightPosition; // Position/Direction of the light source
uniform vec3 cameraPosition;// Position of the camera
uniform vec3 ambientLight;  // Intensities of the ambient light
uniform vec3 directLight;   // Intensities of the direct light
uniform vec3 material;      // Specular/diffuse/ambient reflection constants for the material
uniform float shininess;    // shininess constant for the material
uniform bool useTexture;    // Object uses a texture

out vec3 fragmentColor;
out vec3 fragmentPosition;
out vec3 diffuseColor;
out vec2 fragTexCoord;

void main()
{
	vec3 n = normalize(nm * normal);
	vec3 surfacePos = vec3(model * vec4(position, 1));
	vec3 surfaceToLight;

	// check if this is a directional light
	if(lightPosition.w == 0.0) {
		//directional light
		surfaceToLight = normalize(lightPosition.xyz);
	} else {
		// NOT a directional light
		surfaceToLight = normalize( vec3( lightPosition.xyz - surfacePos ) );
	}

	vec3 v = normalize(surfacePos - cameraPosition);
	vec3 r = normalize(reflect( surfaceToLight, n ));

	float sDotN = max( dot( surfaceToLight, n ), 0.0 );
	vec3 spec = material.x * directLight * pow( max( 0.0, dot(r,v) ), shininess );
	vec3 amb = material.z * ambientLight * color;

	if(useTexture) {
		fragmentColor = spec + amb;
	}
	else {
		vec3 diffuse = material.y * directLight * color * sDotN;
		fragmentColor = diffuse + spec + amb;
	}
	
	diffuseColor = directLight * color * sDotN;
	fragTexCoord = texCoord;
	fragmentPosition = position;
	gl_Position = mvp * vec4(position,  1.0);
}