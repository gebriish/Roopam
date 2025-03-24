#include "line_batch.hpp"
#include <glad/glad.h>

namespace Rpm {

void lineBatchInit(LineBatch2D& batch, size_t size) {
	static constexpr float quadVertices[] = {
		-1.0f, -1.0f,
		1.0f, -1.0f,
		-1.0f,  1.0f,
		1.0f,  1.0f
	};

	batch.capacity = size;
	batch.open = false;
	batch.instanceData.reserve(size);

	glGenVertexArrays(1, &batch.vao);
	glGenBuffers(1, &batch.vboVertices);
	glGenBuffers(1, &batch.vboInstances);

	glBindVertexArray(batch.vao);

	glBindBuffer(GL_ARRAY_BUFFER, batch.vboVertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, batch.vboInstances);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(LineData2D), nullptr, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(LineData2D), (void*)(0));                      // x1,y1,x2,y2
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(LineData2D), (void*)(4 * sizeof(float)));      // color
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(LineData2D), (void*)(8 * sizeof(float)));      // outlineColor
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(LineData2D), (void*)(12 * sizeof(float)));     // thickness, outlineThickness, roundedCaps

	glEnableVertexAttribArray(1); glVertexAttribDivisor(1, 1);
	glEnableVertexAttribArray(2); glVertexAttribDivisor(2, 1);
	glEnableVertexAttribArray(3); glVertexAttribDivisor(3, 1);
	glEnableVertexAttribArray(4); glVertexAttribDivisor(4, 1);

	glBindVertexArray(0);
}

void lineBatchCleanup(LineBatch2D& batch) {
	glDeleteVertexArrays(1, &batch.vao);
	glDeleteBuffers(1, &batch.vboVertices);
	glDeleteBuffers(1, &batch.vboInstances);
	batch.instanceData.clear();
	batch.capacity = 0;
	batch.open = false;
}

void lineBatchBegin(LineBatch2D& batch) {
	batch.open = true;
	batch.instanceData.clear();
}

bool lineBatchAdd(LineBatch2D& batch, float x1, float y1, float x2, float y2,
									float thickness, const fColor& color, const fColor& outlineColor,
									float outlineThickness, bool roundedCaps) {
	if (!batch.open || batch.instanceData.size() >= batch.capacity) return false;

	LineData2D line = { x1, y1, x2, y2, color, outlineColor, thickness, outlineThickness, roundedCaps ? 1.0f : 0.0f };
	batch.instanceData.push_back(line);
	return true;
}

void lineBatchEnd(LineBatch2D& batch) {
	batch.open = false;

	glBindBuffer(GL_ARRAY_BUFFER, batch.vboInstances);
	glBufferSubData(GL_ARRAY_BUFFER, 0, batch.instanceData.size() * sizeof(LineData2D), batch.instanceData.data());
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void lineBatchDraw(LineBatch2D& batch) {
	if(batch.open)
		lineBatchEnd(batch);

	if (batch.instanceData.empty()) return;

	glBindVertexArray(batch.vao);
	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, (GLsizei)batch.instanceData.size());
	glBindVertexArray(0);
}

}
