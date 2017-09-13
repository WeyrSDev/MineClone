#include "WorldGenerator.hpp"

#include "map/Constants.hpp"
#include "map/data/BlockDataBase.hpp"

constexpr int WaterLevel = 40;
WorldGenerator::WorldGenerator(unsigned int seed):
	m_heightMapNoise(seed * seed + 12312)
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
					int wz = z + chunkPosition.y * ChunkLength;
					int h = 60
						+ 40 * m_heightMapNoise.noise(wx, wz, ChunkLength, 1.f / 30.f)
						+ 20 * m_heightMapNoise.noise(wx, wz, ChunkLength, 1.f / 5.f)
						+ 5 * m_heightMapNoise.noise(wx, wz, ChunkLength, 1.f / 2.f);
					for (int y = 0; y <= WaterLevel || y <= h; y++)
					{
						Block block = static_cast<BlockId>(BlocksIds::air);
						
						Block surface = static_cast<BlockId>(BlocksIds::grass);
						Block top = static_cast<BlockId>(BlocksIds::dirt);
						Block interior = static_cast<BlockId>(BlocksIds::stone);

						if (h <= WaterLevel + 2)
						{
							surface = static_cast<BlockId>(BlocksIds::sand);
							top = static_cast<BlockId>(BlocksIds::sand);
						}

						if (y > h)
							block = static_cast<BlockId>(BlocksIds::water);
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
