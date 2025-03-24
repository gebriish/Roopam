#include "quad_batch.hpp"
#include <glad/glad.h>

namespace Rpm {

void quadBatchInit(QuadBatch& batch, size_t size) {
	batch.capacity = size;
	batch.instanceData.reserve(batch.capacity);

	glGenVertexArrays(1, &batch.vao);
	glBindVertexArray(batch.vao);

	float quadVertices[] = {
		0, 0, 
		0, 1,
		1, 0,
		1, 1, 
	};

	glGenBuffers(1, &batch.vboVertices);
	glBindBuffer(GL_ARRAY_BUFFER, batch.vboVertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

	glGenBuffers(1, &batch.vboInstances);
	glBindBuffer(GL_ARRAY_BUFFER, batch.vboInstances);
	glBufferData(GL_ARRAY_BUFFER, batch.capacity * sizeof(QuadData), nullptr, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(QuadData), (void*)0);
	glVertexAttribDivisor(1, 1);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(QuadData), (void*)(4 * sizeof(float)));
	glVertexAttribDivisor(2, 1);

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(QuadData), (void*)(8 * sizeof(float)));
	glVertexAttribDivisor(3, 1);

	glBindVertexArray(0);
}

void quadBatchCleanup(QuadBatch& batch) {
	glDeleteBuffers(1, &batch.vboVertices);
	glDeleteBuffers(1, &batch.vboInstances);
	glDeleteVertexArrays(1, &batch.vao);
	batch.instanceData.clear();
}

void quadBatchBegin(QuadBatch& batch) {
	batch.open = true;
	batch.instanceData.clear();
}

bool quadBatchAdd (
	QuadBatch& batch, 
	float x, float y, float w, float h, 
	float radius, const fColor& color
)  {
	if(!batch.open || batch.instanceData.size() >= batch.capacity) 
		return false;

	QuadData data;
	data.x = x;
	data.y = y;
	data.w = w;
	data.h = h;
	data.color = color;
	data.radius = radius;

	batch.instanceData.push_back(data);

	return true;
}

void quadBatchEnd(QuadBatch& batch) {
	batch.open = false;
}

void quadBatchDraw(QuadBatch& batch) {
	if(batch.open)
		quadBatchEnd(batch);

	if (batch.instanceData.empty()) return;

	glBindVertexArray(batch.vao);

	glBindBuffer(GL_ARRAY_BUFFER, batch.vboInstances);
	glBufferSubData(GL_ARRAY_BUFFER, 0, batch.instanceData.size() * sizeof(QuadData), batch.instanceData.data());

	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, (GLsizei)batch.instanceData.size());

	glBindVertexArray(0);
}

}
