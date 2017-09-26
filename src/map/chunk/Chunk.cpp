#include "Chunk.hpp"

#include "renderer/MasterRenderer.hpp"
#include "Chunk.hpp"
#include "map/MapBase.hpp"
#include "map/data/BlockDataBase.hpp"

ChunkId::ChunkId(sf::Int32 _x, sf::Int32 _z)
{
	x = _x;
	z = _z;
}

ChunkId::operator ChunkKey ()
{
	sf::Int32 arr[2] = {x, z};

	return *((sf::Int64*) arr);
}

Chunk::Chunk(Vec2 position, const MapBase* const map) :
	m_position(position), m_map(map)
{
	m_sections.resize(ChunkHeight);
	int i = 0;
	for (auto& section : m_sections)
	{
		section = ChunkSection(Vec3(position.x, i++, position.y), m_map);
	}
}

void Chunk::setBlock(int x, int y, int z, Block block)
{
	if (outOfBound(x, y, z))
	{
		return;
	}

	int sy = y % ChunkLength;
	int i = y / ChunkLength;

	m_sections[y / ChunkLength].setBlock(x, sy, z, block);

	if (x == 0)
	{
		auto chunk = m_map->getChunk(m_position.x - 1, m_position.y);
		if (chunk)
		{
			chunk->getSection(i).modify();
		}
	}
	if (x == 15)
	{
		auto chunk = m_map->getChunk(m_position.x + 1, m_position.y);
		if (chunk)
		{
			chunk->getSection(i).modify();
		}
	}
	
	if (z == 0)
	{
		auto chunk = m_map->getChunk(m_position.x, m_position.y - 1);
		if (chunk)
		{
			chunk->getSection(i).modify();
		}
	}
	if (z == 15)
	{
		auto chunk = m_map->getChunk(m_position.x, m_position.y + 1);
		if (chunk)
		{
			chunk->getSection(i).modify();
		}
	}
	if (sy == 0)
	{
		getSection(i - 1).modify();
	}
	if (sy == 15 && y < BlockHeight)
	{
		getSection(i + 1).modify();
	}
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
	int sy = y % ChunkLength;

	return m_sections[y / ChunkLength].getBlock(x, sy, z);
}

void Chunk::update(MasterRenderer& renderer)
{
	for (auto& section : m_sections)
	{
		section.update();
		renderer.addChunk(section);
	}
}

ChunkSection& Chunk::getSection(unsigned int i)
{
	return m_sections[i % ChunkHeight];
}

Vec3 Chunk::toWorldPosition(int x, int y, int z) const
{
	return Vec3(x + m_position.x * ChunkLength, y, z + m_position.y * ChunkLength);
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
