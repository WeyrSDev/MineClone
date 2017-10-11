#include "AABB.hpp"

AABB::AABB(Vec3 _pos, Vec3 _size):
	pos(_pos), size(_size)
{ }

bool AABB::collide(const AABB& aabb)
{
	return pos.x + size.x > aabb.pos.x &&
		pos.x < aabb.pos.x + aabb.size.x &&
		
		pos.y + size.y > aabb.pos.y &&
		pos.y < aabb.pos.y + aabb.size.y &&

		pos.z + size.z > aabb.pos.z &&
		pos.z < aabb.pos.z + aabb.size.z;
}
