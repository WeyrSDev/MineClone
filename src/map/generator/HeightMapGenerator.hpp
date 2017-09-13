#pragma once

#include "util/Noise.hpp"

class HeightMapGenerator {
public:
	HeightMapGenerator(unsigned int seed);

	unsigned int getHeight(int x, int z);
private:
	unsigned int interpolation(float left, float right, float delta);
	unsigned int getPointHeight(int x, int z);
	Noise m_heightMap1, m_heightMap2, m_heightMap3;
};
