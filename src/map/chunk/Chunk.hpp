#pragma once

#include "ChunkSection.hpp"
#include "map/Constants.hpp"

class Chunk {
public:
	Chunk(sf::Vector2i position, const MapBase* const map);

	Block getBlock(int x, int y, int z) const;
	void setBlock(int x, int y, int z, Block block);
	
	void update();

private:
	sf::Vector3i toWorldPosition(int x, int y, int z) const;
	bool outOfBound(int x, int y, int z) const;

	const sf::Vector2i m_position;

	std::vector<ChunkSection> m_sections;
	const MapBase* const m_map;
};
