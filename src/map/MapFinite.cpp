#include "MapFinite.hpp"

#include <stdlib.h>
#include <time.h>

#include "util/Noise.hpp"
#include "data/BlockDataBase.hpp"

MapFinite::MapFinite(unsigned int size) :
	m_chunkSize(size), m_blockSize(size * ChunkLength)
{
	srand(time(NULL));

	unsigned int seed = rand();
	Noise noise(seed);

	printf("Creating world\n");
	sf::Clock clock;
	for (int i = 0; i < m_chunkSize; i++)
	{
		for (int e = 0; e < m_chunkSize; e++)
		{
			m_chunks.push_back(Chunk(Vec2(e, i), this));
			auto& chunk = m_chunks.back();

			for (int x = 0; x < ChunkLength; x++)
			{
				for (int z = 0; z < ChunkLength; z++)
				{
					double tx = ((double) x / ChunkLength) + e;
					double tz = ((double) z / ChunkLength) + i;
					tx /= 8.f; tz /= 8.f;

					int h = 40 + 40 * noise.noise(tx, tz);
					for (int y = 0; y <= h; y++)
					{
						Block block = static_cast<BlockId>(BlocksIds::stone);
						if (y == h)
							block = static_cast<BlockId>(BlocksIds::grass);
						else if (y > h - 5)
							block = static_cast<BlockId>(BlocksIds::dirt);

						chunk.setBlock(x, y, z, block);
					}
				}
			}
		}
	}
	printf("World created in %f seconds\n", clock.getElapsedTime().asSeconds());
	printf("Generating chunk mesh data\n");
	clock.restart();
	for (int i = 0; i < m_chunkSize; i++)
	{
		for (int e = 0; e < m_chunkSize; e++)
		{
			for (int y = 0; y < ChunkHeight; y++)
			{
				auto& chunk = m_chunks[i * m_chunkSize + e].getSection(y);
				chunk.regenerateMeshData();
			}
		}
	}
	printf("Generated chunk mesh data in %f seconds\n", clock.getElapsedTime().asSeconds());

}

MapFinite::~MapFinite()
{

}

void MapFinite::update(MasterRenderer& renderer)
{
	for (auto& chunk : m_chunks)
	{
		chunk.update(renderer);
	}
}

Block MapFinite::getBlock(int x, int y, int z) const
{
	if (outOfBounds(x, z) || y >= BlockHeight)
	{
		return 0;
	}

	if (y < 0)
	{
		return 1;
	}

	int cx = x / ChunkLength;
	int cz = z / ChunkLength;

	int rx = x % ChunkLength;
	int rz = z % ChunkLength;

	return m_chunks[cz * m_chunkSize + cx].getBlock(rx, y, rz);
}

void MapFinite::setBlock(int x, int y, int z, Block block)
{
	if (outOfBounds(x, z) || y >= BlockHeight || y < 0)
	{
		return;
	}

	int cx = x / ChunkLength;
	int cz = z / ChunkLength;

	int rx = x % ChunkLength;
	int rz = z % ChunkLength;

	m_chunks[cz * m_chunkSize + cx].setBlock(rx, y, rz, block);
}

bool MapFinite::outOfBounds(int x, int z) const
{
	if (x < 0 || x >= m_blockSize)
		return true;
	if (z < 0 || z >= m_blockSize)
		return true;

	return false;
}
