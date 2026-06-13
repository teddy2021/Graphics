#version 460 core

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D tex;
uniform vec3 colour;

void main(){
	vec4 color = vec4(colour, 1);
	FragColor = texture( tex, TexCoord );
}
