#include "BlockData.hpp"

BlockData::BlockData(Vec2 top, Vec2 bottom, Vec2 sides, bool _collidable):
	collbox(Vec3(0, 0, 0), Vec3(1, 1, 1)),
	hitbox(Vec3(0, 0, 0), Vec3(1, 1, 1))
{
	texTop = top;
	texBottom = bottom;
	texLeft = sides;
	texRight = sides;
	texFront = sides;
	texBack = sides;

	collidable = _collidable;
	hasHitbox = _collidable;
}
