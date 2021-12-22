#version 330 core

//in vec3 vertexColor;
in vec2 textCoord;

uniform sampler2D myTexture;
uniform sampler2D myTexture2;

uniform float fade;

out vec4 fragColor;

void main() {
	vec4 textColor = mix(texture(myTexture, textCoord), texture(myTexture2, textCoord), fade);
	if (textColor.a < 0.1)
		discard;	
	fragColor = textColor;
}
