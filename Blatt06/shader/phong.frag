#version 330 core

in vec3 outColor;
smooth in vec3 n;
smooth in vec3 surfacePos;
in vec3 fragmentPosition;
in vec2 fragTexCoord;

uniform sampler2D imgTexture;
uniform bool useTexture;
uniform vec3 origin;
uniform vec3 centerAxis;
uniform bool calcTC;

uniform vec4 lightPosition;  // Position/Direction of the light source
uniform vec3 ambientLight;   // Intensities of the ambient light
uniform vec3 directLight;    // Intensities of the direct light
uniform vec3 material;       // Specular/diffuse/ambient reflection constants for the material
uniform float shininess;     // shininess constant for the material
uniform vec3 cameraPosition; // Viewpoint position

out vec3 fragColor;

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
		if(calcTC) {
			float s;
			float t;
			vec3 u = normalize(centerAxis);
			float d = length(u.yz);
			if(d > 0.0) {
				vec3 transformedPos = (rotationY(-d, u.x) * rotationX(-u.z/d, -u.y/d) * translate(-origin) * vec4(fragmentPosition, 1)).xyz;
				if (transformedPos.y > 0) {
					t = 1.0 - (acos(transformedPos.x / length(transformedPos.xy)) / (2*3.141592653589));
				} else {
					t = (acos(transformedPos.x / length(transformedPos.xy)) / (2*3.141592653589));
				}
			}
			else {
				vec3 transformedPos = (translate(-origin) * vec4(fragmentPosition, 1)).xyz;
				if (transformedPos.y > 0) {
					t = 1.0 - (acos(transformedPos.z / length(transformedPos.yz)) / (2*3.141592653589));
				} else {
					t = (acos(transformedPos.z / length(transformedPos.yz)) / (2*3.141592653589));
				}
			}
			s = 1.0 - dot(centerAxis, (fragmentPosition - origin)) / (pow(length(centerAxis),2.0));
			diffuse = texture(imgTexture, vec2(s,t)).xyz * directLight * outColor * sDotN;
		}
		else {
			diffuse = texture(imgTexture, fragTexCoord).xyz * directLight * outColor * sDotN;
		}
		
	}
	else {
		diffuse = material.y * directLight * outColor * sDotN;
	}

	vec3 spec = material.y * directLight * pow( max( 0.0, dot(r,v) ), shininess );
	vec3 amb = material.z * ambientLight * outColor;

	fragColor = diffuse + spec + amb;
}