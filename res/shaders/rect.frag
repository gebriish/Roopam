#version 410 core

uniform vec4 uFillColor;
uniform vec4 uOutlineColor;
uniform vec2 uMinPos;
uniform vec2 uMaxPos;
uniform float uRadius;
uniform float uOutlineThickness;

in struct {
	vec2 position;
} vsOut;

out vec4 FragColor;

float sdfBox(vec2 position, vec2 halfSize, float cornerRadius) {
   position = abs(position) - halfSize + cornerRadius;
   return length(max(position, 0.0)) + min(max(position.x, position.y), 0.0) - cornerRadius;
}

void main() {
	vec2 rectCenter = (uMaxPos + uMinPos) * 0.5;
	vec2 halfSize = (uMaxPos - uMinPos) * 0.5;
	vec2 pos = vsOut.position - rectCenter;
	float sdfDist = sdfBox(pos, halfSize, uRadius);
	float mask = smoothstep(.5, -.5, sdfDist);

	vec4 col = uFillColor;
	if(uOutlineThickness > 0.5f) {
		float outlineMask = 1.0 - smoothstep(.5 - uOutlineThickness, -.5 - uOutlineThickness, sdfDist);
		col = mix(uFillColor, uOutlineColor, outlineMask);
	}

	FragColor = vec4(col.rgb,col.a * mask); 
}
