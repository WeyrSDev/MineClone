#include "Functions.hpp"

#include "Constants.hpp"

Vec3 getBlockFromPoint(Vec3 point)
{
	auto dx = point.x - (int) point.x;
	auto dy = point.y - (int) point.y;
	auto dz = point.z - (int) point.z;

	if (dx < 0) dx = 1 + dx;
	if (dy < 0) dy = 1 + dy;
	if (dz < 0) dz = 1 + dz;

	return Vec3(point.x - dx, point.y - dy, point.z - dz);
}

ChunkId getChunkFromBlock(int x, int z)
{
	auto rPos = toChunkRelativePosition(x, 0, z);
	return ChunkId((x - rPos.x) / ChunkLength, (z - rPos.z) / ChunkLength);
}

Vec3 toChunkRelativePosition(int x, int y, int z)
{
	x %= ChunkLength;
	if (x < 0) x += ChunkLength;
	z %= ChunkLength;
	if (z < 0) z += ChunkLength;

	return Vec3(x, y, z);
}
