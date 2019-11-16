#version 330 core

out vec4 FragColor;

//in vec3 color;
in vec2 uvs;

uniform sampler2D textureMap;

void main() {
    FragColor = texture(textureMap, uvs);
}