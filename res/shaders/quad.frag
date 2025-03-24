#version 460 core

in vec2 fPos;
in vec4 fRect;
in vec4 fColor;
in float fRadius;

out vec4 FragColor;


void main() {
	vec2 localPos = fPos - fRect.xy;
	vec2 localUV = localPos / fRect.zw;
	
	vec2 pointInBox = vec2(clamp(localPos.x, fRadius, fRect.z - fRadius), 
			clamp(localPos.y, fRadius, fRect.w - fRadius));

	vec2 deltaPos = localPos - pointInBox;
	float l = length(deltaPos);

	float edge = 1.0;
	float mask = smoothstep(fRadius, fRadius - edge, l);
	FragColor = vec4(fColor.rgb, fColor.a * mask);
}
