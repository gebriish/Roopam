#version 460 core
layout (location = 0) in vec2 vertexPos;
layout (location = 1) in vec4 rect; // x, y, w, h
layout (location = 2) in vec4 color;
layout (location = 3) in float radius;

out vec2 fPos;
out vec4 fRect;
out vec4 fColor;
out float fRadius;

uniform mat4 uProj;

void main() {
    vec2 scaledPos = vertexPos * rect.zw + rect.xy;
    gl_Position = uProj * vec4(scaledPos, 0.0, 1.0);
	
		fPos = scaledPos;
		fColor = color;
		fRadius = radius;
		fRect = rect;
}
