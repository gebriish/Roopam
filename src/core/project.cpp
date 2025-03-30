#include "project.hpp"
#include "action_map.hpp"
#include <iostream>
#include <thread>
#include <atomic>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <renderer/renderer.hpp>
#include <renderer/shader.hpp>
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

		//=============================================================
		// Input polling Pass
		//=============================================================
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

		//=============================================================
		// Update Pass
		//=============================================================
		onUpdate(deltaTime);

		//=============================================================
		// Animation Pass
		//=============================================================
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
