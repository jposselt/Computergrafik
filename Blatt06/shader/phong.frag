#version 330 core

in vec3 outColor;
smooth in vec3 n;
smooth in vec3 surfacePos;
in vec2 fragTexCoord;

uniform sampler2D imgTexture;
uniform bool useTexture;

uniform vec4 lightPosition;  // Position/Direction of the light source
uniform vec3 ambientLight;   // Intensities of the ambient light
uniform vec3 directLight;    // Intensities of the direct light
uniform vec3 material;       // Specular/diffuse/ambient reflection constants for the material
uniform float shininess;     // shininess constant for the material
uniform vec3 cameraPosition; // Viewpoint position

out vec3 fragColor;

void main()
{
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

	vec3 diffuse;
	if(useTexture) {
		diffuse = texture(imgTexture, fragTexCoord).xyz * directLight * outColor * sDotN;
	}
	else {
		diffuse = material.y * directLight * outColor * sDotN;
	}

	vec3 spec = material.y * directLight * pow( max( 0.0, dot(r,v) ), shininess );
	vec3 amb = material.z * ambientLight * outColor;

	fragColor = diffuse + spec + amb;
}