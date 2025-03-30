#include "renderer.hpp"
#include "../core/vmath.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdio>

#include "shader.hpp"

namespace Rpm 
{

//======================================================================//
//                      GLOBAL Render State                             //
//======================================================================//

static struct {
	DrawList mainDrawList;
	GLuint rectVAO, rectVBO;

	Shader rectShader;
	Shader lineShader;

	bool initialized;


} g_RenderState;

inline static void _draw_rect(const RectData& data) {
	float vertices[] = {
		data.begin.x, data.begin.y,
		data.begin.x, data.end.y,
		data.end.x,   data.begin.y,
		data.end.x,   data.end.y,
	};

	glBindBuffer(GL_ARRAY_BUFFER, g_RenderState.rectVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	shaderUseProgram(g_RenderState.rectShader);
	shaderUploadFloat(g_RenderState.rectShader, "uRadius", data.cornderRadius);
	shaderUploadFloat3(g_RenderState.rectShader, "uFillColor", data.fillColor.r, data.fillColor.g, data.fillColor.b);
	shaderUploadFloat2(g_RenderState.rectShader, "uMinPos", data.begin.x, data.begin.y);
	shaderUploadFloat2(g_RenderState.rectShader, "uMaxPos", data.end.x, data.end.y);
	

	glBindVertexArray(g_RenderState.rectVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

inline static void _draw_line(const LineData& data) {
	float vertices[] = {
		-1, -1,
		-1,  1,
		 1, -1,
		 1,  1,
	};

	glBindBuffer(GL_ARRAY_BUFFER, g_RenderState.rectVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	shaderUseProgram(g_RenderState.lineShader);
	shaderUploadFloat(g_RenderState.lineShader, "uThickness", data.thickness);
	shaderUploadFloat3(g_RenderState.lineShader, "uFillColor", data.fillColor.r, data.fillColor.g, data.fillColor.b);
	shaderUploadFloat2(g_RenderState.lineShader, "uBeginPos", data.begin.x, data.begin.y);
	shaderUploadFloat2(g_RenderState.lineShader, "uEndPos", data.end.x, data.end.y);

	glBindVertexArray(g_RenderState.rectVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void renderInit() {
	if(g_RenderState.initialized) {
		printf("Renderer already initialized!");
		return;
	}

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("Failed to load OpenGL\n");
		return;
	}

	
	// Rect Mesh Initialization
	{
		glGenVertexArrays(1, &g_RenderState.rectVAO);
		glGenBuffers(1, &g_RenderState.rectVBO);

		glBindVertexArray(g_RenderState.rectVAO);
		glBindBuffer(GL_ARRAY_BUFFER, g_RenderState.rectVBO);

		glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), nullptr, GL_DYNAMIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	shaderLoadGlsl(g_RenderState.rectShader, "res/shaders/rect.vert", "res/shaders/rect.frag");
	shaderLoadGlsl(g_RenderState.lineShader, "res/shaders/rect_line.vert", "res/shaders/rect_line.frag");

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	g_RenderState.initialized= true;
}

void renderCleanup() {
	if(!g_RenderState.initialized) {
		return;
	}

	// Rect Mesh Cleanup
	{
		glDeleteVertexArrays(1, &g_RenderState.rectVAO);
		glDeleteBuffers(1, &g_RenderState.rectVBO);
	}

	shaderDeleteProgram(g_RenderState.rectShader);
	shaderDeleteProgram(g_RenderState.lineShader);

	g_RenderState.initialized = false;
}

void renderSetViewport(int width, int height) {
	glViewport(0, 0, width, height);

	const vmath::mat4 proj = vmath::mat4::orthographic(0, width, height, 0, -100, 100);

	shaderUseProgram(g_RenderState.rectShader);
	shaderUploadMat4(g_RenderState.rectShader, "uProj", proj.elements);
	shaderUseProgram(g_RenderState.lineShader);
	shaderUploadMat4(g_RenderState.lineShader, "uProj", proj.elements);
}

void renderClearViewport(float color[4]) {
	glClearColor(color[0], color[1], color[2], color[3]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

DrawList& renderMainDrawList() {
	return g_RenderState.mainDrawList;
}

void renderDrawAll() {
	const auto& commands = g_RenderState.mainDrawList.getDrawCommands();

	for(const DrawCommand& command : commands) {
		switch(command.type) {
			case Rpm::DrawCommandType::RECT :
				_draw_rect(command.rectData);
			break;

			case Rpm::DrawCommandType::LINE :
				_draw_line(command.lineData);
			break;

			default:
			break;
		}
	}
}

void renderFlushData() {
	g_RenderState.mainDrawList.flush();
}

}
