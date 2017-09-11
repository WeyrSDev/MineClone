#pragma once

#include "ChunkSection.hpp"
#include "util/Vector.hpp"

class ChunkBuilder
{
public:
	ChunkBuilder(const ChunkSection& chunkSection);

	MeshData getData();
private:
	void pushSolidBlock(int x, int y, int z);
	void pushFace(Vec3 start, Vec3 right, Vec3 down, float light, Vec2 texture);
	bool isVisible(int x, int y, int z);

	MeshData& m_currentMesh;
	MeshData m_solidMesh;

	const ChunkSection& m_chunk;

	Block currentBlock;
};
