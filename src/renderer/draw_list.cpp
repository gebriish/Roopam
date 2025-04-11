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

void DrawList::addCircle(const CircleData& data) {
	RectData rectData;
	rectData.begin = data.center - data.radius;
	rectData.end = data.center + data.radius;
	rectData.fillColor = data.fillColor;
	rectData.outlineThickness = data.outlineThickness;
	rectData.outlineColor = data.outlineColor;
	rectData.cornerRadius = data.radius;
	this->addRect(rectData);
}

void DrawList::flush() {
	mDrawCommands.clear();
}

}
