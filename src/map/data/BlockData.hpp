#pragma once

#include "util/AABB.hpp"

struct BlockData {
public:
	BlockData(Vec2 top, Vec2 bottom, Vec2 sides, bool collidable = true);

	AABB collbox, hitbox;

	Vec2 texTop, texBottom, texLeft, texRight, texFront, texBack; 
	bool collidable;
	bool hasHitbox;
};
