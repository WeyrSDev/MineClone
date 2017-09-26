#include "BlockData.hpp"

BlockData::BlockData(Vec2 top, Vec2 bottom, Vec2 sides, bool _collidable)
{
	texTop = top;
	texBottom = bottom;
	texLeft = sides;
	texRight = sides;
	texFront = sides;
	texBack = sides;

	collidable = _collidable;
}
