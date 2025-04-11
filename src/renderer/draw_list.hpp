#pragma once
#include "../utils/vmath.hpp"
#include "color.hpp"
#include <vector>

namespace Rpm 
{

constexpr size_t POLYGON_MAX_SIZE = 32;

enum class DrawCommandType {
	LINE,
	RECT,
};

struct LineData{  
	vec2   begin; 
	vec2   end; 
	float  thickness = 4.0f; 
	fColor fillColor = {1, 1, 1, 1};
	float outlineThickness = 0.0f;
	fColor outlineColor = {0, 0, 0, 1};
};
		
struct RectData { 
	vec2   begin;
	vec2   end; 
	float  cornerRadius 		 = 4.0f; 
	fColor fillColor         = fColor {1,1,1,1};
	float  outlineThickness  = 0.0f;
	fColor outlineColor      = fColor {0,0,0,1};
};

struct CircleData {
	vec2   center;
	float  radius             = 5.0f;
	fColor fillColor          = fColor {1,1,1,1};
	float  outlineThickness   = 0.0f;
	fColor outlineColor       = fColor {0,0,0,1};
};

struct DrawCommand {
	DrawCommandType type;
	union {
		LineData lineData;
		RectData rectData;
		// for now circles are made with rects
	};
};

class DrawList {
public:
	void addLine(const LineData& data);
	void addRect(const RectData& data);
	void addCircle(const CircleData& data);
	void flush();

	inline void reserve(size_t capacity) {
		mDrawCommands.reserve(capacity);
	}

	inline const std::vector<DrawCommand>& getDrawCommands() const { return mDrawCommands; }

private:
	std::vector<DrawCommand> mDrawCommands;
};

}
