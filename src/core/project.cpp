#include "project.hpp"
#include "action_map.hpp"
#include <iostream>
#include <thread>
#include <atomic>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <renderer/renderer.hpp>
#include <renderer/quad_batch.hpp>
#include <renderer/shader.hpp>
#include <renderer/line_batch.hpp>
#include <core/vmath.hpp>

namespace Rpm {

ProjectBase::ProjectBase(int width, int height)
{
	mWindow = windowInitialize(
		width, height, "roopam",
		WINDOWFLAG_CENTERED | WINDOWFLAG_VSYNC | WINDOWFLAG_RESIZABLE
	);
	inputSetWindow(mWindow);

	renderInit();
	renderSetViewport(width, height);

	mRunning = true;
}

void ProjectBase::start()
{
	std::thread commandThread(&ProjectBase::_command_loop, this);

	float lastTime = windowGetSeconds();

	while (mRunning) {
		const float currentTime = windowGetSeconds();
		const float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		Event e;
		while (windowGetEvent(e)) {
			switch (e.type) {
				case EVENT_QUIT:
					mRunning = false;
					break;
				case EVENT_RESIZE : {
					auto& data = e.resize_data;
					renderSetViewport(data.width, data.height);
					break;
				}
				default:
					break;
			}
		}

		LoopFunction funcToRun = nullptr;
		{
			std::unique_lock<std::mutex> lock(mMutex);
			if(mCurrentLoopFunc) {
				funcToRun = mCurrentLoopFunc;
			}
		}

		if(funcToRun) {
			bool finished = funcToRun(); 
			if(finished) {
				std::unique_lock<std::mutex> lock(mMutex);
				mCurrentLoopFunc = nullptr;
				mIsPlaying = false;
				mCV.notify_one();
			}
		}

		float x, y;
		x = 320;
		y = 240;


		fColor color;
		colorLoadHexcode("121312", color.rgba);
		renderClearViewport(color.rgba);

		colorLoadHexcode("504945", color.rgba);

		LineStyle lineStyle;
		lineStyle.thickness = 6;


		lineStyle.fillColor = {1, 1, 1, 1};
		float dx = 400 / 15.0f;
		float dTheta = VMATH_PI * 2 / 15.0f;
		for (int i =0; i <= 15; i++ ) {
			float x = 80 + i *  dx;
			float theta =	dTheta * i + 0.2 + windowGetSeconds();
			float h = sin(theta) * 100;
			renderAddLine2d(x, 250 + sin(windowGetSeconds() * 5 + i * dTheta) * 40, x, 250 - h, lineStyle);
		}

		lineStyle.fillColor = color;
		renderAddLine2d(30,440, 30, 50, lineStyle);
		renderAddLine2d(30,440, 600, 440, lineStyle);

		renderDrawLine2Ds();
		renderDrawQuads();

		onUpdate(deltaTime);

		actionMapUpdate();
		windowPollEvents(mWindow);
		windowSwapBuffers(mWindow);
	}


	renderCleanup();
	windowDestroy(mWindow);

	commandThread.join();
}

void ProjectBase::_command_loop()
{
	std::string expr;
	while (mRunning) {
		std::getline(std::cin, expr);
		if (expr.empty()) continue;

		if (expr == "exit") {
			mRunning = false;
		} else {
			onCommand(expr);
		}
	}
}

void ProjectBase::play(LoopFunction func)
{
	std::unique_lock<std::mutex> lock(mMutex);
	mCurrentLoopFunc = func;
	mIsPlaying = true;
	mCV.wait(lock, [this]() { return !mIsPlaying; });
}

} // namespace Rpm
