#version 330 core

in vec3 fragmentColor;
in vec3 diffuseColor;
in vec2 fragTexCoord;

uniform sampler2D imgTexture;
uniform bool useTexture;

out vec3 fragColor;

void main()
{
	if(useTexture) {
		fragColor = fragmentColor + texture(imgTexture, fragTexCoord).xyz * diffuseColor;
	}
	else {
		fragColor = fragmentColor;
	}
	
}