#version 460 core
layout (location = 0) in vec2 vPos;

out vec2 fPos;

uniform mat4 modelmat;
uniform mat4 viewmat;
uniform mat4 projmat;

vec4 pos = vec4(vPos, 0.f, 1.f);

void main() {
    fPos = vPos;
    gl_Position = projmat*viewmat*modelmat*pos;
}