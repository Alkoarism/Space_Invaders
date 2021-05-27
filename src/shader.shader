#VERTEX

#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTextCoord;

out vec2 textCoord;

void main() {
	gl_Position = vec4(aPos, 1.0);
	textCoord = aTextCoord;
}

#VERTEX_END

#FRAGMENT

#vesion 330 core

in vec3 vertexColor;
in vec2 textCoord;

uniform sampler2D myTexture;
uniform sampler2D myTexture2;

out vec4 fragColor;

void main() {
	fragColor = mix(texture(myTexture, textCoord), texture(mytexture2, textCoord), 0.2f);
}

#FRAGMENT_END