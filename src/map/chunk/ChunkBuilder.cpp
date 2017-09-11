#include "ChunkBuilder.hpp"
#include "ChunkSection.hpp"
#include "util/MeshUtil.hpp"
#include "map/data/BlockDataBase.hpp"

ChunkBuilder::ChunkBuilder(const ChunkSection& chunkSection):
	m_chunk(chunkSection), m_currentMesh(m_solidMesh)
{
	for(int y = 0; y < ChunkLength; y++)
	{
		for(int z = 0; z < ChunkLength; z++)
		{
			for(int x = 0; x < ChunkLength; x++)
			{
				currentBlock = m_chunk.getBlock(x, y, z);

				if (currentBlock == (BlockId)BlocksIds::air)
					continue;
				pushSolidBlock(x, y, z);
			}
		}
	}
}

MeshData ChunkBuilder::getData()
{
	return m_solidMesh;
}

void ChunkBuilder::pushSolidBlock(int x, int y, int z)
{
	m_currentMesh = m_solidMesh;
	auto data = currentBlock.getData();

	//Front face
	if (isVisible(x, y, z + 1))
	{
		pushFace(Vec3(x, y + 1, z + 1), Vec3(1, 0, 0), Vec3(0, -1, 0), 0.8, data.texFront);
	}
	//Back face
	if (isVisible(x, y, z - 1))
	{
		pushFace(Vec3(x + 1, y + 1, z), Vec3(-1, 0, 0), Vec3(0, -1, 0), 0.8, data.texBack);
	}
	//Left face
	if (isVisible(x - 1, y, z))
	{
		pushFace(Vec3(x, y + 1, z), Vec3(0, 0, 1), Vec3(0, -1, 0), 0.6, data.texLeft);
	}
	//Right face
	if (isVisible(x + 1, y, z))
	{
		pushFace(Vec3(x + 1, y + 1, z + 1), Vec3(0, 0, -1), Vec3(0, -1, 0), 0.6, data.texRight);
	}
	//Top face
	if (isVisible(x, y + 1, z))
	{
		pushFace(Vec3(x, y + 1, z), Vec3(1, 0, 0), Vec3(0, 0, 1), 1, data.texTop);
	}
	//Bottom face
	if (isVisible(x, y - 1, z))
	{
		pushFace(Vec3(x + 1, y, z), Vec3(-1, 0, 0), Vec3(0, 0, 1), 0.4, data.texBottom);
	}
}

void ChunkBuilder::pushFace(Vec3 start, Vec3 right, Vec3 down, float light, Vec2 texture)
{
	start = m_chunk.toWorldPosition(start.x, start.y, start.z);
	MeshUtil::pushFace(m_currentMesh, start, right, down, texture * AtlasUnit, Vec2(AtlasUnit, AtlasUnit), light);
}

bool ChunkBuilder::isVisible(int x, int y, int z)
{
	Block sideBlock = m_chunk.getBlock(x, y, z);
	if (sideBlock == (BlockId) BlocksIds::air)
	{
		return true;
	}
	return false;
}
