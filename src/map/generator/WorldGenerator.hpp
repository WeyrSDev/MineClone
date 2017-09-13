#pragma once

#include "HeightMapGenerator.hpp"
#include "map/chunk/Chunk.hpp"
#include "util/Noise.hpp"

class WorldGenerator {
public:
	WorldGenerator(unsigned int seed);

	void generateChunk(Chunk& chunk);
private:
	HeightMapGenerator m_heightMap;
};
