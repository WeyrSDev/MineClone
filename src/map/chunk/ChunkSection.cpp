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

ChunkSection::ChunkSection(ChunkSection&& chunk):
	m_map(chunk.m_map), m_position(chunk.m_position), m_modified(chunk.m_modified),
	m_modifyMeshes(chunk.m_modifyMeshes)
{
	m_blocks = std::move(chunk.m_blocks);
	m_meshes = std::move(chunk.m_meshes);
}

ChunkSection& ChunkSection::operator=(ChunkSection&& chunk)
{
	m_map = chunk.m_map;
	m_position = chunk.m_position;
	m_modified = chunk.m_modified;
	m_modifyMeshes = chunk.m_modifyMeshes;

	m_blocks = std::move(chunk.m_blocks);
	m_meshes = std::move(chunk.m_meshes);

	return *this;
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

		m_meshes.solidData.clear();
		m_meshes.liquidData.clear();

		m_modifyMeshes = false;
	}
}

void ChunkSection::regenerateMeshData()
{
	ChunkBuilder builder(*this);

	m_meshes.solidData = std::move(builder.getSolidData());
	m_meshes.liquidData = std::move(builder.getLiquidData());
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
