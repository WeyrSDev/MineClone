#pragma once

#include "ChunkSection.hpp"
#include "util/Vector.hpp"

class ChunkBuilder
{
public:
	ChunkBuilder(const ChunkSection& chunkSection);

	MeshData& getSolidData();
	MeshData& getLiquidData();
private:
	void pushBlock(int x, int y, int z);
	void pushFace(Vec3 start, Vec3 right, Vec3 down, float light, Vec2 texture);
	bool isVisible(int x, int y, int z);

	MeshData* m_currentMesh;
	MeshData m_solidMesh, m_liquidMesh;

	const ChunkSection& m_chunk;

	Block currentBlock;
};
