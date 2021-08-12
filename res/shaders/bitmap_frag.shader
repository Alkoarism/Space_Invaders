#version 330 core

in vec2 textCoord;
in vec4 vertexColor;

uniform sampler2D myTexture;
uniform sampler2D myTexture2;

out vec4 fragColor;

void main() {
	vec4 textColor = texture(myTexture, textCoord) * vertexColor;
	if (textColor.a < 0.1)
		discard;
	fragColor = textColor;
}