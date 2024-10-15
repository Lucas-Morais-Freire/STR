#version 460 core
in vec2 fPos;

out vec4 color;

uniform vec3 fColor;
uniform vec2 center;
uniform float radius;

void main() {
    if ((fPos.x - center.x)*(fPos.x - center.x) + (fPos.y - center.y)*(fPos.y - center.y) <= radius*radius) {
        color = vec4(fColor, 1.f);
    } else {
        color = vec4(0.0, 0.0, 0.0, 1.0);
    }
}