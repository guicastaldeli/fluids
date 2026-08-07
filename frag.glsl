#version 330 core

in vec2 uv;

out vec4 fragColor;

void main() {
    //fragColor = vec4(uv.x, uv.y, 1.0 - uv.x * uv.y, 1.0);
    fragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}