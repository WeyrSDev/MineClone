#include "Chunk.hpp"

#include "Chunk.hpp"
#include "map/MapBase.hpp"

Chunk::Chunk(sf::Vector2i position, const MapBase* const map) :
	m_position(position), m_map(map)
{

	for (int i = 0; i < ChunkHeight; i++)
	{
		m_sections.push_back(ChunkSection(sf::Vector3i(position.x, i, position.y), m_map));
	}
}

void Chunk::setBlock(int x, int y, int z, Block block)
{
	if (outOfBound(x, y, z))
	{
		return;
	}

	int sz = z % ChunkLength;

	m_sections[z / ChunkLength].setBlock(x, y, sz, block);
}

Block Chunk::getBlock(int x, int y, int z) const
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

	int sz = z % ChunkLength;

	return m_sections[z / ChunkLength].getBlock(x, y, sz);
}

void Chunk::update()
{
	for (auto& section : m_sections)
	{
		section.update();
	}
}

sf::Vector3i Chunk::toWorldPosition(int x, int y, int z) const
{
	return sf::Vector3i(x + m_position.x * ChunkLength, y, z + m_position.y * ChunkLength);
}

bool Chunk::outOfBound(int x, int y, int z) const
{
	if (x < 0 || x >= ChunkLength)
	{
		return true;
	}

	if (z < 0 || z >= ChunkLength)
	{
		return true;
	}

	if (y < 0 || y >= BlockHeight)
	{
		return true;
	}
	return false;
}
