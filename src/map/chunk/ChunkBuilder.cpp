#include "ChunkBuilder.hpp"
#include "ChunkSection.hpp"
#include "util/MeshUtil.hpp"

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

				if (!currentBlock)
					continue;
				pushSolidBlock(x, y, z);
			}
		}
	}
}

Mesh ChunkBuilder::generateMesh()
{
	return Mesh(m_solidMesh);
}

void ChunkBuilder::pushSolidBlock(int x, int y, int z)
{
	m_currentMesh = m_solidMesh;

	//Front face
	if (isVisible(x, y, z + 1))
	{
		pushFace(Vec3(x, y + 1, z + 1), Vec3(1, 0, 0), Vec3(0, -1, 0), 0.8, Vec2(currentBlock, 0));
	}
	//Back face
	if (isVisible(x, y, z - 1))
	{
		pushFace(Vec3(x + 1, y + 1, z), Vec3(-1, 0, 0), Vec3(0, -1, 0), 0.8, Vec2(currentBlock, 0));
	}
	//Left face
	if (isVisible(x - 1, y, z))
	{
		pushFace(Vec3(x, y + 1, z), Vec3(0, 0, 1), Vec3(0, -1, 0), 0.6, Vec2(currentBlock, 0));
	}
	//Right face
	if (isVisible(x + 1, y, z))
	{
		pushFace(Vec3(x + 1, y + 1, z + 1), Vec3(0, 0, -1), Vec3(0, -1, 0), 0.6, Vec2(currentBlock, 0));
	}
	//Top face
	if (isVisible(x, y + 1, z))
	{
		pushFace(Vec3(x, y + 1, z), Vec3(1, 0, 0), Vec3(0, 0, 1), 1, Vec2(currentBlock, 0));
	}
	//Bottom face
	if (isVisible(x, y - 1, z))
	{
		pushFace(Vec3(x, y, z), Vec3(1, 0, 0), Vec3(0, 0, 1), 0.4, Vec2(currentBlock, 0));
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
	if (sideBlock == 0)
	{
		return true;
	}
	return false;
}
