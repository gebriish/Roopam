#pragma once
#include "color.hpp"

namespace Rpm {

struct LineStyle {
	fColor fillColor {1,1,1,1};
	fColor outlineColor {1, 1, 0.5, 1};
	float thickness = 10, outlineThickness = 0;
	bool roundedCaps = true;
};

void renderInit();
void renderCleanup();

void renderSetViewport(int width, int height);
void renderClearViewport(float color[4]);

void renderAddQuad(float x, float y, float w, float h, float radius = 1.0f, const fColor& color = {1, 1, 1, 1});
void renderAddLine2d(float x1, float y1, float x2, float y2, const LineStyle& style);

void renderDrawQuads();
void renderDrawLine2Ds();

}

