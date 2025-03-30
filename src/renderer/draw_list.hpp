#pragma once
#include "../core/vmath.hpp"
#include "color.hpp"
#include <vector>

namespace Rpm 
{

enum class DrawCommandType {
	LINE,
	RECT,
};

struct LineData{  
	vmath::vec2 begin, end; 
	fColor fillColor = {1, 1, 1, 1};
	float thickness = 4.0f; 
};

		
struct RectData { 
	vmath::vec2 begin, end; 
	fColor fillColor = {1, 1, 1, 1};
	float cornderRadius = 4.0f; 
};

struct DrawCommand {
	DrawCommandType type;
	union {
		LineData lineData;
		RectData rectData;
	};
};

class DrawList {
public:

	void addLine(const LineData& data);
	void addRect(const RectData& data);

	void flush();

	inline void reserve(size_t capacity) {
		mDrawCommands.reserve(capacity);
	}

	inline const std::vector<DrawCommand> getDrawCommands() const { return mDrawCommands; }

private:
	std::vector<DrawCommand> mDrawCommands;
};

}
