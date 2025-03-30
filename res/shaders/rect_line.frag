#version 410 core
uniform float uThickness;
uniform vec3 uFillColor;
uniform vec2 uBeginPos;
uniform vec2 uEndPos;

in struct {
	vec2 position;
} vsOut;

out vec4 FragColor;

float sdfLine(in vec2 p, in vec2 a, in vec2 b) {
	vec2 ba = b - a;
	vec2 pa = p - a;
	float h = clamp(dot(pa, ba) / dot(ba, ba), 0., 1.);
	return length(pa - h * ba);
}

void main() {
	vec2 dir = normalize(uEndPos - uBeginPos);

	float halfThickness = uThickness * 0.5;
	float l = length(uBeginPos - uEndPos);

	float d = sdfLine(vsOut.position, uBeginPos, uEndPos);
	float mask = smoothstep(halfThickness, halfThickness-1, d);

	FragColor = vec4(uFillColor, mask);
}
