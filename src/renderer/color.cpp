#include "color.hpp"
#include <cstdio>

namespace Rpm {

void colorLoadHexcode(const char* hex, float array[4]) {
	uint32_t r, g, b;
	sscanf(hex, "%02x%02x%02x", &r, &g, &b);
	array[0] = r / 255.0f;
	array[1] = g / 255.0f;
	array[2] = b / 255.0f;
	array[3] = 1.0f;
}

}
