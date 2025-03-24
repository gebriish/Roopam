#pragma once
#include <vector>
#include "color.hpp"

namespace Rpm {

struct LineData2D {
	float x1, y1;
	float x2, y2;
	fColor color;          	
	fColor outlineColor;   
	float thickness;       
	float outlineThickness;
	float roundedCaps;     
};

struct LineBatch2D {
	unsigned int vao, vboVertices, vboInstances;
	std::vector<LineData2D> instanceData;
	size_t capacity;
	bool open;
};

void lineBatchInit(LineBatch2D& batch, size_t size);
void lineBatchCleanup(LineBatch2D& batch);

void lineBatchBegin(LineBatch2D& batch);
bool lineBatchAdd(LineBatch2D& batch, float x1, float y1, float x2, float y2, 
                  float thickness = 1.0f, 
                  const fColor& color = {1,1,1,1}, 
                  const fColor& outlineColor = {0,0,0,0}, 
                  float outlineThickness = 0.0f, 
                  bool roundedCaps = true);
void lineBatchEnd(LineBatch2D& batch);
void lineBatchDraw(LineBatch2D& batch);

}
