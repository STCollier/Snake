#version 330 core

out vec4 FragColor;

in vec2 TexCoord;
uniform sampler2D _texture;

uniform vec4 headColor;

void main() {
	FragColor = texture(_texture, TexCoord) * headColor;
}