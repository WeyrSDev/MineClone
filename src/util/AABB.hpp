#pragma once

#include "Vector.hpp"

struct AABB {
	AABB() = default;
	AABB(Vec3 _pos, Vec3 _size);

	bool collide(const AABB& aabb);

	Vec3 pos, size;
};
