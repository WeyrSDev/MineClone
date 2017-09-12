#include "MapFinite.hpp"

#include "util/Noise.hpp"

MapFinite::MapFinite(unsigned int size, unsigned int seed) :
	m_chunkSize(size), m_blockSize(size * ChunkLength),
	generator(seed)
{
	Noise noise(seed);

	printf("Creating world\n");
	sf::Clock clock;
	for (int i = 0; i < m_chunkSize; i++)
	{
		for (int e = 0; e < m_chunkSize; e++)
		{
			m_chunks.push_back(Chunk(Vec2(e, i), this));
			generator.generateChunk(m_chunks.back());

		}
	}
	printf("World created in %f seconds\n\n", clock.getElapsedTime().asSeconds());
	
	printf("Generating chunk mesh data\n\n");
	clock.restart();
	for (int z = 0; z < m_chunkSize; z++)
	{
		for (int x = 0; x < m_chunkSize; x++)
		{
			for (int y = 0; y < ChunkHeight; y++)
			{
				auto& chunk = m_chunks[z * m_chunkSize + x].getSection(y);
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
