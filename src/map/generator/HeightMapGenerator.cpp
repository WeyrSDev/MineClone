#include "HeightMapGenerator.hpp"

#include <stdio.h>
#include "map/Constants.hpp"

constexpr int BaseLevel = 50;

HeightMapGenerator::HeightMapGenerator(unsigned int seed):
	m_heightMap1(seed + 1232131),
	m_heightMap2 (seed * seed + seed + 2137312),
	m_heightMap3 (seed - 439876)
{

}

unsigned int HeightMapGenerator::interpolation(float left, float right, float delta)
{
	return left + (right - left) * delta;
}

unsigned int HeightMapGenerator::getHeight(int x, int z)
{
	constexpr int s = 4;

	int top = (z / s) * s;
	int left = (x / s) * s;

	if (z < 0) top -= s;
	if (x < 0) left -= s;

	float zDelta = (float) (z - top) / s;
	float xDelta = (float) (x - left) /  s;

	int h1 = getPointHeight(left, top);
	int h2 = getPointHeight(left + s, top);
	int h3 = getPointHeight(left, top + s);
	int h4 = getPointHeight(left + s, top + s);
	
	int i1 = interpolation(h1, h2, xDelta);
	int i2 = interpolation(h3, h4, xDelta);

	return interpolation(i1, i2, zDelta);
}

unsigned int HeightMapGenerator::getPointHeight(int x, int z)
{
	unsigned int h1 = 50 * m_heightMap1.noise(x, z, ChunkLength, 1.f / 20.f)
		+ 10 * m_heightMap1.noise(x, z, ChunkLength, 1.f / 2.f);
	unsigned int h2 =  10
		+ 40 * m_heightMap2.noise(x, z, ChunkLength, 1.f / 10.f)
		+ 15 * m_heightMap2.noise(x, z, ChunkLength, 1.f / 3.f);

	float noise = m_heightMap3.noise(x, z, ChunkLength, 1.f / 5.f);

	return BaseLevel + (noise < 0.25f ? h1 : h2);
}
