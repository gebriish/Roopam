#version 410 core
uniform float uThickness;
uniform float uOutlineThickness;
uniform vec4 uFillColor;
uniform vec4 uOutlineColor;
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
	float mask = smoothstep(halfThickness + .5, halfThickness - .5, d);
	
	vec4 col = uFillColor;

	if (uOutlineThickness > 0.5) {
		float radiusToOutline = halfThickness - uOutlineThickness;
		float outlineMask = 1.0 - smoothstep(radiusToOutline + 0.5, radiusToOutline - .5, d);
		col = mix(col, uOutlineColor, outlineMask);
	}

	FragColor = vec4(col.rgb, col.a * mask);
}
