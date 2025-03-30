#version 410 core
layout (location = 0) in vec2 aPos;

uniform mat4 uProj;

out struct {
	vec2 position;
} vsOut;

void main() {
	vsOut.position = aPos;
	gl_Position = uProj * vec4(aPos, 0.0, 1.0);
}
