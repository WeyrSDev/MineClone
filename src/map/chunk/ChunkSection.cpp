#include "ChunkSection.hpp"

#include "map/MapBase.hpp"
#include "ChunkBuilder.hpp"

int getIndex(int x, int y, int z)
{
	return z * ChunkArea + y * ChunkLength + x;
}

ChunkSection::ChunkSection(Vec3 position, const MapBase* const map):
	m_position(position), m_map(map), m_modified(false), m_modifyMeshes(false)
{
	for (auto& block : m_blocks)
	{
		block = 0;
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
	m_modified = true;
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

		return m_map->getBlock(wx, wy, wz);
	}
	return m_blocks[getIndex(x, y, z)];
}

void ChunkSection::update()
{
	if (m_modified)
	{
		regenerateMeshData();
	}

	if (m_modifyMeshes)
	{
		m_meshes.solid = Mesh(m_meshes.solidData);
		m_meshes.liquid = Mesh(m_meshes.liquidData);

		m_modifyMeshes = false;
	}
}

void ChunkSection::regenerateMeshData()
{
	ChunkBuilder builder(*this);

	m_meshes.solidData = builder.getSolidData();
	m_meshes.liquidData = builder.getLiquidData();
	m_modifyMeshes = true;
	m_modified = false;
}

Vec3 ChunkSection::toWorldPosition(int x, int y, int z) const
{
	return Vec3(x + m_position.x * ChunkLength, y + m_position.y * ChunkLength, z + m_position.z * ChunkLength);
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
