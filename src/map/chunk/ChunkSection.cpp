#include "ChunkSection.hpp"

#include "map/MapBase.hpp"

int getIndex(int x, int y, int z)
{
	return z * ChunkArea + y * ChunkLength + x;
}

ChunkSection::ChunkSection(sf::Vector3i position, const MapBase* const map):
	m_position(position), m_map(map)
{
	for (auto block : m_blocks)
	{
		block = 1;
	}
}

void ChunkSection::setBlock(int x, int y, int z, Block block)
{
	if (outOfBound(x, y, z))
	{
		return;
	}

	int sz = z % ChunkLength;

	m_blocks[getIndex(x, y, z)] = block;
}

Block ChunkSection::getBlock(int x, int y, int z) const
{
	if (outOfBound(x, y, z))
	{
		int wx, wy, wz;
		auto v = toWorldPosition(x, y, z);
		wx = v.x;
		wy = v.y;
		wz = v.z;

		return m_map->getBlock(x, y, z);
	}
	return m_blocks[getIndex(x, y, z)];
}

void ChunkSection::update()
{

}

sf::Vector3i ChunkSection::toWorldPosition(int x, int y, int z) const
{
	return sf::Vector3i(x + m_position.x * ChunkLength, y + m_position.y * ChunkLength, z + m_position.z * ChunkLength);
}

bool ChunkSection::outOfBound(int x, int y, int z) const
{
	if (x < 0 || x >= ChunkLength)
	{
		return true;
	}

	if (z < 0 || z >= ChunkLength)
	{
		return true;
	}

	if (y < 0 || y >= ChunkLength)
	{
		return true;
	}
	return false;
}
