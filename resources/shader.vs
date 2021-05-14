#version 450 core

layout (location = 0) in vec3 aPos;

out vec2 c;

uniform float zoom;
uniform float tlx;
uniform float tly;

void main() {
    gl_Position = vec4(aPos, 1.0);
    c = (zoom * aPos.xy) + vec2(tlx, tly);
}
