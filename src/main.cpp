#include <cstdio>
#include <core/project.hpp>
#include <core/action_map.hpp>
#include <core/input.hpp>
#include <renderer/renderer.hpp>
#include <renderer/color.hpp>

#define MOUSE_0 0

class MyProject : public Rpm::ProjectBase 
{
	bool firstFrame = true;

public:

	MyProject()
	: Rpm::ProjectBase(1000, 625)
	{
	}

private:
	void init() {
		Rpm::renderMainDrawList().reserve(1024);
	}

	void onUpdate(float deltaTime) override {
		if(firstFrame) {
			this->init();
			firstFrame = false;
		}

		float x, y; 
		Rpm::inputGetCursorPosition(x, y);

		Rpm::DrawList& drawlist = Rpm::renderMainDrawList();
		Rpm::LineData line = Rpm::LineData{.begin = vec2(20), .end = vec2(x, y), .thickness = 10};
		line.fillColor = Rpm::fColor::fromHex("131313");
		line.outlineColor = Rpm::fColor::fromHex("ebdbc7");
		line.outlineThickness = 1;
		drawlist.addLine(line);

		Rpm::renderClearViewport(Rpm::fColor::fromHex("131313").rgba);
		Rpm::renderDrawAll();

		Rpm::renderFlushData();
	}

	void onCommand(const std::string& command) override {
	}

};


int main() {
	MyProject proj;
	proj.start();
}
