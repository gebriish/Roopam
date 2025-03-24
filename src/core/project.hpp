#pragma once

#include <string>
#include <functional>
#include <atomic>
#include <condition_variable>
#include <core/window.hpp>

namespace Rpm {

using LoopFunction = std::function<bool()>;

//----------------------------------------------------------------------------------
// Base class for project
//----------------------------------------------------------------------------------
class ProjectBase
{
public:
	ProjectBase(int width, int height);
	virtual ~ProjectBase() = default;

	void start();

protected:
	virtual void onUpdate(float dt) = 0;
	virtual void onCommand(const std::string& command) = 0;

	void play(LoopFunction func);

private:
	void _command_loop();

private:
	Window* mWindow = nullptr;
	std::atomic<bool> mRunning{ false };

	std::mutex mMutex;
	std::condition_variable mCV;
	LoopFunction mCurrentLoopFunc = nullptr;
	bool mIsPlaying = false;
};

} // namespace Rpm
