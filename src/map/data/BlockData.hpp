#pragma once

#include "util/Vector.hpp"

struct BlockData {
public:
	BlockData(Vec2 top, Vec2 bottom, Vec2 sides);

	Vec2 texTop, texBottom, texLeft, texRight, texFront, texBack; 
};
