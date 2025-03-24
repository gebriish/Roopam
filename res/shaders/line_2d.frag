#version 330 core

in vec4 vLineColor;
in vec4 vOutlineColor;
in float vThickness;
in float vOutlineThickness;
in float vRoundedCaps;
in float vLength;
in vec2 vLocalPos;

out vec4 FragColor;

void main() {
	
	vec4 color;

	float edge = 1.0;

	if(vRoundedCaps > 0.5) {
		float radius = vThickness * 0.5;
		vec2 p = vec2(clamp(vLocalPos.x, radius, vLength - radius), radius);
		float l = length(vLocalPos - p);

		float mask1 = smoothstep(radius, radius - edge, l);

		if (vOutlineThickness > 0.0) {
			float mask2 = 1.0 - smoothstep(radius - vOutlineThickness, radius - vOutlineThickness - edge, l);
			vec4 lineCol = mix(vLineColor, vOutlineColor, mask2);
			color = vec4(lineCol.rgb, lineCol.a * mask1);
		}
		else {
			color = vec4(vLineColor.rgb, vLineColor.a * mask1);
		}
	}
	else {
		float halfThickness = vThickness * 0.5;

		float distLeft   = vLocalPos.x;
		float distRight  = vLength - vLocalPos.x;
		float distTop    = vThickness - vLocalPos.y;
		float distBottom = vLocalPos.y;

		float maskX = smoothstep(0.0, edge, min(distLeft, distRight));
		float maskY = smoothstep(0.0, edge, min(distTop, distBottom));
		float lineMask = maskX * maskY;

		float outlineMaskX = smoothstep(vOutlineThickness + edge, vOutlineThickness, min(distLeft, distRight));
		float outlineMaskY = smoothstep(vOutlineThickness + edge, vOutlineThickness, min(distTop, distBottom));
		float outlineMask = clamp(0, 1, outlineMaskX + outlineMaskY);

		vec4 lineCol = mix(vLineColor,vOutlineColor, outlineMask);
		color = vec4(lineCol.rgb, lineCol.a * lineMask);
	}

	FragColor = color;
}
