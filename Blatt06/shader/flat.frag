#version 330 core

flat in vec3 fragmentColor;
in vec3 fragmentPosition;
in vec3 diffuseColor;
in vec2 fragTexCoord;

uniform sampler2D imgTexture;
uniform bool useTexture;
uniform vec3 origin;
uniform vec3 centerAxis;
uniform bool calcTC;

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
			fragColor = fragmentColor + texture(imgTexture, vec2(s,t)).xyz * diffuseColor;
		}
		else {
			fragColor = fragmentColor + texture(imgTexture, fragTexCoord).xyz * diffuseColor;
		}
	}
	else {
		fragColor = fragmentColor;
	}
}