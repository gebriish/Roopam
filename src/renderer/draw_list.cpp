#include "draw_list.hpp"

namespace Rpm 
{

void DrawList::addLine(const LineData& data) {
	DrawCommand command {};
	command.type = DrawCommandType::LINE;
	command.lineData = data;

	mDrawCommands.push_back(command);
}

void DrawList::addRect(const RectData& data) {
	DrawCommand command {};
	command.type = DrawCommandType::RECT;
	command.rectData = data;

	mDrawCommands.push_back(command);
}

void DrawList::flush() {
	mDrawCommands.clear();
}

}
