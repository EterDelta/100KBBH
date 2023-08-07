#version 330 core

layout(location = 0) in vec3 posistion;
uniform mat4 transform;

void main() {
    gl_Position = transform * vec4(posistion, 1.0);
}
