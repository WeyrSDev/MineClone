#pragma once

#include <vector>
#include <memory>

#include "MapBase.hpp"
#include "generator/WorldGenerator.hpp"

class MapFinite : public MapBase {
public:
	MapFinite(unsigned int size, unsigned int seed);
	~MapFinite();

	Block getBlock(int x, int y, int z) const;
	void setBlock(int x, int y, int z, Block block);
	void update(MasterRenderer& renderer);
private:
	bool outOfBounds(int x, int z) const;

	const unsigned int m_chunkSize, m_blockSize;

	std::vector<Chunk> m_chunks;

	WorldGenerator generator;
};
