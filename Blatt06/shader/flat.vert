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

uniform vec3 origin;
uniform vec3 centerAxis;
uniform bool calcTC;

flat out vec3 fragmentColor;
out vec3 diffuseColor;
out vec2 fragTexCoord;

mat4 rotationX( in float c, in float s ) {
	return mat4(	1.0,	0,	0,	0,
			  0, 	c,     -s,	0,
			  0, 	s,	c,	0,
			  0, 	0,	0, 	1.0);
}

mat4 rotationY( in float c, in float s) {
	return mat4(	 c,	0,	s,	0,
			 0,	1.0,	0,	0,
			-s,	0,	c,	0,
			 0, 	0,	0,	1.0);
}

mat4 translate( in vec3 v ) {
	return mat4(	1.0,	0,	0,	v.x,
			0,	1.0,	0,	v.y,
			0,	0, 	1.0,	v.z,
			0, 	0,	0,	1.0);
}

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
	vec3 r = reflect( surfaceToLight, n );

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
	gl_Position = mvp * vec4(position,  1.0);

	if (calcTC) {
		vec3 u = normalize(centerAxis);
		float d = sqrt(u.y*u.y + u.z*u.z);
		vec3 transformedPos = (rotationY(-d, u.x) * rotationX(-u.z/d, -u.y/d) * translate(-origin) * vec4(position, 1)).xyz;

		float s = transformedPos.z / length(centerAxis);
		//float s = ((position.y + 2.0) / 4.0);
		float t;
		float l = length(transformedPos.xy);
		if (transformedPos.y > 0) {
			t = 1.0 - (acos(transformedPos.x / l) / (2*3.141592653589));
		} else {
			t = (acos(transformedPos.x / l) / (2*3.141592653589));
		}

		fragTexCoord = vec2(s,t);
	} else {
		fragTexCoord = texCoord;
	}
}