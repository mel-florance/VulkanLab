#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUvs;
layout (location = 2) in vec3 aNormal;

out vec2 uvs;
out vec3 normal;
out vec3 worldPos;
out vec3 camPos;
out vec3 position;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 transform;

void main() {
    uvs = aUvs;
    normal = mat3(transpose(inverse(transform))) * aNormal;
    position = vec3(transform * vec4(aPos, 1.0));
    gl_Position = projection * view * transform * vec4(aPos, 1.0);
}