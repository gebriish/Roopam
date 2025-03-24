#include "renderer.hpp"
#include "quad_batch.hpp"
#include "line_batch.hpp"
#include "shader.hpp"
#include <core/vmath.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdio>

namespace Rpm 
{

//======================================================================//
//                      GLOBAL Render State                             //
//======================================================================//

static struct {
	QuadBatch quadBatch;
	Shader quadShader;
	std::vector<QuadData> quadBuffer;

	LineBatch2D line2dBatch;
	Shader line2dShader;
	std::vector<LineData2D> line2dBuffer;

	bool initialized;
} g_RenderState;


void renderInit() {
	if(g_RenderState.initialized) {
		printf("Renderer already initialized!");
		return;
	}

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("Failed to load OpenGL\n");
		return;
	}
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	quadBatchInit(g_RenderState.quadBatch, 512);
	shaderLoadGlsl(g_RenderState.quadShader, "res/shaders/quad.vert", "res/shaders/quad.frag");
	g_RenderState.quadBuffer.reserve(1024);

	lineBatchInit(g_RenderState.line2dBatch, 512);
	shaderLoadGlsl(g_RenderState.line2dShader, "res/shaders/line_2d.vert", "res/shaders/line_2d.frag");
	g_RenderState.line2dBuffer.reserve(1024);

	g_RenderState.initialized= true;
}

void renderCleanup() {
	if(!g_RenderState.initialized) {
		return;
	}

	shaderDeleteProgram(g_RenderState.quadShader);
	quadBatchCleanup(g_RenderState.quadBatch);

	shaderDeleteProgram(g_RenderState.line2dShader);
	lineBatchCleanup(g_RenderState.line2dBatch);

	g_RenderState.initialized = false;
}

void renderSetViewport(int width, int height) {
	glViewport(0, 0, width, height);

	const mat4 proj = mat4::orthographic(0, width, height, 0, -1, 100);
	shaderUseProgram(g_RenderState.quadShader);
	shaderUploadMat4(g_RenderState.quadShader, "uProj", proj.elements);
	shaderUseProgram(g_RenderState.line2dShader);
	shaderUploadMat4(g_RenderState.line2dShader, "uProj", proj.elements);
}

void renderClearViewport(float color[4]) {
	glClearColor(color[0], color[1], color[2], color[3]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void renderAddQuad(float x, float y, float w, float h, float radius, const fColor& color) {
	g_RenderState.quadBuffer.push_back(QuadData{x, y, w, h, color, radius});
}

void renderDrawQuads() {
	if(g_RenderState.quadBuffer.empty()) return;

	shaderUseProgram(g_RenderState.quadShader);
		
	quadBatchBegin(g_RenderState.quadBatch);
	for(const auto& data : g_RenderState.quadBuffer) {
		if(!quadBatchAdd(g_RenderState.quadBatch, data.x, data.y, data.w, data.h, data.radius, data.color)) {
			quadBatchEnd(g_RenderState.quadBatch);
			quadBatchDraw(g_RenderState.quadBatch);
			quadBatchBegin(g_RenderState.quadBatch);
		}
	}

	quadBatchEnd(g_RenderState.quadBatch);
	quadBatchDraw(g_RenderState.quadBatch);
	g_RenderState.quadBuffer.clear();
}

void renderAddLine2d(float x1, float y1, float x2, float y2, const LineStyle& style) {
	g_RenderState.line2dBuffer.push_back(LineData2D 
		{
			x1, y1, x2, y2, 
			style.fillColor, style.outlineColor, 
			style.thickness, style.outlineThickness,
			style.roundedCaps ? 1.0f : 0.0f
		});
}

void renderDrawLine2Ds() {
	if(g_RenderState.line2dBuffer.empty()) return;

	shaderUseProgram(g_RenderState.line2dShader);
		
	lineBatchBegin(g_RenderState.line2dBatch);
	for(const auto& data : g_RenderState.line2dBuffer) {
		if(!lineBatchAdd(g_RenderState.line2dBatch, data.x1, data.y1, data.x2, data.y2, data.thickness,
									 data.color, data.outlineColor, data.outlineThickness, data.roundedCaps)) {
			lineBatchEnd(g_RenderState.line2dBatch);
			lineBatchDraw(g_RenderState.line2dBatch);
			lineBatchBegin(g_RenderState.line2dBatch);
		}
	}

	lineBatchEnd(g_RenderState.line2dBatch);
	lineBatchDraw(g_RenderState.line2dBatch);
	g_RenderState.line2dBuffer.clear();
}

}
