#pragma once

#include "map/chunk/Chunk.hpp"
#include "util/Noise.hpp"

class WorldGenerator {
public:
	WorldGenerator(unsigned int seed);

	void generateChunk(Chunk& chunk);
private:
	Noise m_heightMapNoise;
};
