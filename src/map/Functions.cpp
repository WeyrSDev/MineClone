#include "Functions.hpp"

#include "Constants.hpp"

Vec3 getBlockFromPoint(Vec3 point)
{
	int bx = point.x;
	int by = point.y;
	int bz = point.z;

	if (point.x < 0) bx --;
	if (point.z < 0) bz --;

	return Vec3(bx, by, bz);
}

ChunkId getChunkFromBlock(int x, int z)
{
	int xRes = x / ChunkLength;
	int zRes = z / ChunkLength;

	if (x < 0 && x % ChunkLength != 0) xRes--;
	if (z < 0 && z % ChunkLength != 0) zRes--;

	return ChunkId(xRes, zRes);
}

Vec3 toChunkRelativePosition(int x, int y, int z)
{
	x %= ChunkLength;
	if (x < 0) x += ChunkLength;
	z %= ChunkLength;
	if (z < 0) z += ChunkLength;

	return Vec3(x, y, z);
}
