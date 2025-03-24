#pragma once
#include "color.hpp"
#include <vector>

namespace Rpm {

struct QuadData {
	float x, y;
	float w, h;
	fColor color;
	float radius;
};

struct QuadBatch {
	unsigned int vao, vboVertices, vboInstances;
	std::vector<QuadData> instanceData;
	size_t capacity;
	bool open;
};

void quadBatchInit(QuadBatch& batch, size_t size);
void quadBatchCleanup(QuadBatch& batch);

void quadBatchBegin(QuadBatch& batch);
bool quadBatchAdd(QuadBatch& batch, float x, float y, float w, float h,
									float radius = 0.0f, const fColor& color = {1,1,1,1});
void quadBatchEnd(QuadBatch& batch);

void quadBatchDraw(QuadBatch& batch);

}
