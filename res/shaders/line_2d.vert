#version 330 core

layout (location = 0) in vec2 quadVertex;       // Quad vertices (-1 to 1, for width and height scaling)
layout (location = 1) in vec4 linePoints;       // x1, y1, x2, y2
layout (location = 2) in vec4 lineColor;        // rgba
layout (location = 3) in vec4 outlineColor;     // rgba
layout (location = 4) in vec3 lineParams;       // thickness, outlineThickness, roundedCaps (0 or 1)

out vec4 vLineColor;
out vec4 vOutlineColor;
out float vThickness;
out float vOutlineThickness;
out float vRoundedCaps;
out float vLength;
out vec2 vLocalPos;

uniform mat4 uProj;

void main() {
	float totalThickness = lineParams.x + lineParams.y * 2;
	vec2 p1 = linePoints.xy;
	vec2 p2 = linePoints.zw;

	vec2 dir = normalize(p2 - p1);
	float length = length(p2 - p1) + totalThickness;
	vec2 normal = vec2(-dir.y, dir.x);

	vec2 _offset = dir * (quadVertex.x * length * 0.5) 
		+ normal * (quadVertex.y * (totalThickness) * 0.5);

	vec2 worldPos = (p1 + p2) * 0.5 + _offset;

	vLineColor = lineColor;
	vOutlineColor = outlineColor;
	vThickness = totalThickness;
	vOutlineThickness = lineParams.y;
	vRoundedCaps = lineParams.z;
	vLocalPos = vec2(quadVertex.x * 0.5 + 0.5, quadVertex.y * 0.5 + 0.5) * vec2(length, totalThickness);
	vLength = length;
	gl_Position = uProj * vec4(worldPos, 0.0, 1.0);
}
