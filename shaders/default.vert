#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aUvs;

out vec3 color;
out vec2 uvs;

void main() {
//    color = aColor;
    uvs = aUvs;
    gl_Position = vec4(aPos, 1.0);
}