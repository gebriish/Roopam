#pragma once
#include "../utils/vmath.hpp"
#include <vector>

namespace Rpm {

struct Mesh2D {
	std::vector<vec2> vertices;
	std::vector<unsigned int> indices;
};

}
