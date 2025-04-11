#include "color.hpp"
#include <cstdio>

namespace Rpm {


fColor fColor::fromHex(const char* hexcode) {
	fColor result;
	uint32_t r, g, b;
	sscanf(hexcode, "%02x%02x%02x", &r, &g, &b);
	result.rgba[0] = r / 255.0f;
	result.rgba[1] = g / 255.0f;
	result.rgba[2] = b / 255.0f;
	result.rgba[3] = 1.0f;
	return result;
}

}
