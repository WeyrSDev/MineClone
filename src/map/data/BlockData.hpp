#pragma once

#include "util/Vector.hpp"

struct BlockData {
public:
	BlockData(Vec2 top, Vec2 bottom, Vec2 sides, bool collidable = true);

	Vec2 texTop, texBottom, texLeft, texRight, texFront, texBack; 
	bool collidable;
};
