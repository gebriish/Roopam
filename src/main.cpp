#include <cstdio>
#include <core/project.hpp>
#include <core/input.hpp>
#include <renderer/renderer.hpp>
#include <renderer/color.hpp>
#include <renderer/shader.hpp>
#include <core/vmath.hpp>

class MyProject : public Rpm::ProjectBase 
{
	bool firstFrame = true;
public:

	MyProject()
	: Rpm::ProjectBase(640, 480)
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
		drawlist.addRect(Rpm::RectData { {10, 10}, {x,y} , Rpm::fColor::fromHex("fabd2f"), 10 });
		drawlist.addRect(Rpm::RectData { {x,y}, {630,470} , Rpm::fColor::fromHex("b16286"), 10 });
		drawlist.addLine(Rpm::LineData { {600, 400} ,{x, y}, {1, 1, 1, 1}, 10} );

		Rpm::renderClearViewport(Rpm::fColor::fromHex("000000").rgba);

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
