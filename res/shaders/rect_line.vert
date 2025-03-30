#version 410 core
layout (location = 0) in vec2 aPos;

uniform float uThickness;
uniform vec2 uBeginPos;
uniform vec2 uEndPos;
uniform mat4 uProj;

out struct {
	vec2 position;
} vsOut;

void main() {
	vec2 dir = normalize(uEndPos - uBeginPos);
	vec2 perp = vec2(-dir.y, dir.x);

	vec2 midPos = (uBeginPos + uEndPos) * 0.5;
	float halfThickness = uThickness * 0.5;
	float halfLength = length(uEndPos - uBeginPos) * 0.5 + halfThickness;

	vec2 pos = midPos + aPos.x * halfLength * dir + aPos.y * halfThickness * perp;

	vsOut.position = pos;

	gl_Position = uProj * vec4(pos, 0.0, 1.0);
}
