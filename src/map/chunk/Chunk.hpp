#pragma once

#include "ChunkSection.hpp"
#include "map/Constants.hpp"

class MasterRenderer;

class Chunk {
public:
	Chunk(Vec2 position, const MapBase* const map);

	Vec3 toWorldPosition(int x, int y, int z) const;

	Block getBlock(int x, int y, int z) const;
	void setBlock(int x, int y, int z, Block block);
	
	void update(MasterRenderer& renderer);

	ChunkSection& getSection(unsigned int i);
private:
	bool outOfBound(int x, int y, int z) const;

	const Vec2 m_position;

	std::vector<ChunkSection> m_sections;
	const MapBase* const m_map;
};
