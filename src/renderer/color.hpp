#pragma once 
#include <cstdint> 

namespace Rpm {

struct fColor {
	union {
		struct {float r, g, b, a;};
		float rgba[4];
	};
};

struct uColor {
	union {
		struct {uint8_t r, g, b, a;};
		uint8_t rgba[4];
	};
};

void colorLoadHexcode(const char* hex, float array[4]);

}
