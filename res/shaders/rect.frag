#version 410 core

uniform vec3 uFillColor;
uniform vec2 uMinPos;
uniform vec2 uMaxPos;
uniform float uRadius;

in struct {
	vec2 position;
} vsOut;

out vec4 FragColor;

float sdfBox(vec2 position, vec2 halfSize, float cornerRadius) {
   position = abs(position) - halfSize + cornerRadius;
   return length(max(position, 0.0)) + min(max(position.x, position.y), 0.0) - cornerRadius;
}

void main() {
	vec2 pos = vsOut.position - (uMinPos + uMaxPos) * 0.5;
	float sdfDist = sdfBox(pos, (uMaxPos - uMinPos) * 0.5, uRadius);
	float mask = smoothstep(0, -1, sdfDist);

	FragColor = vec4(uFillColor, mask); 
}
