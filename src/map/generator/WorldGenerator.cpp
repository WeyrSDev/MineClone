#include "WorldGenerator.hpp"

#include "map/Constants.hpp"
#include "map/data/BlockDataBase.hpp"

constexpr int WaterLevel = 60;

enum class Biomes {
	ocean,
	desert, beach,
	hills
};

Biomes getBiome(int height, float temp)
{

	if (height < WaterLevel)
	{
		return Biomes::ocean;
	}

	if (temp < -0.2f && height < 80)
	{
		return Biomes::desert;
	}

	if (temp < 0.1 && height < WaterLevel + 3)
	{
		return Biomes::beach;
	}

	return Biomes::hills;
}

WorldGenerator::WorldGenerator(unsigned int seed):
	m_heightMap(seed * seed + 12312),
	m_temperature(seed * seed + seed * 4 + 7432)
{

}

void WorldGenerator::generateChunk(Chunk& chunk)
{
	auto chunkPosition = chunk.getPosition();
	for (int x = 0; x < ChunkLength; x++)
	{
		int wx = x + chunkPosition.x * ChunkLength;
		for (int z = 0; z < ChunkLength; z++)
		{
			Block surface = (BlockId) (BlocksIds::grass);
			Block top = (BlockId) (BlocksIds::dirt);
			Block interior = (BlockId) BlocksIds::stone;

			int wz = z + chunkPosition.y * ChunkLength;

			int h = m_heightMap.getHeight(wx, wz);
			float temp = m_temperature.noise(wx, wz, ChunkLength, 1.f / 10.f);

			if (getBiome(h, temp) != Biomes::hills)
			{
				surface = (BlockId) BlocksIds::sand;
				top = (BlockId) BlocksIds::sand;
			}

			for (int y = 0; y <= WaterLevel || y <= h; y++)
			{
				Block block = (BlockId) BlocksIds::air;
				

				if (y > h)
					block = (BlockId) BlocksIds::water;
				else if (y == h)
					block = surface;
				else if (y > h - 5)
					block = top;
				else if (y < h)
					block = interior;
				
				chunk.setBlock(x, y, z, block);
			}
		}
	}
}
