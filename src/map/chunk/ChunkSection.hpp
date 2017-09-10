#pragma once

#include <array>
#include <memory>

#include <SFML/Graphics.hpp>

#include "Mesh.hpp"
#include "map/Constants.hpp"

typedef unsigned int Block;

class MapBase;

class ChunkSection
{
public:
	ChunkSection(sf::Vector3i position, const MapBase* const map);

	void setBlock(int x, int y, int z, Block Block);
	Block getBlock(int x, int y, int z) const;
	const sf::Vector3i& getPosition() const { return m_position; };

	void update();
	void modify() { m_modified = true; };


	const Mesh* getMesh() const { return &m_mesh; };

private:
	bool outOfBound(int x, int y, int z) const;
	sf::Vector3i toWorldPosition(int x, int y, int z) const;

	bool m_modified = false;
	const sf::Vector3i m_position;
	std::array<Block, ChunkVolume> m_blocks;
	Mesh m_mesh;
	const MapBase* const m_map;
};
