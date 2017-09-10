#include "MapFinite.hpp"

MapFinite::MapFinite(unsigned int size) :
	m_chunkSize(size), m_blockSize(size * ChunkLength)
{

	for (int i = 0; i < m_chunkSize; i++)
	{
		for (int e = 0; e < m_chunkSize; e++)
		{
			m_chunks.push_back(Chunk(sf::Vector2i(e, i), this));
		}
	}
}


MapFinite::~MapFinite()
{

}

Block MapFinite::getBlock(int x, int y, int z) const
{
	if (outOfBounds(x, z) || z >= BlockHeight)
	{
		return 0;
	}

	if (z < 0)
	{
		return 1;
	}

	int cx = x / ChunkLength;
	int cz = z / ChunkLength;

	int rx = x % ChunkLength;
	int rz = z % ChunkLength;

	m_chunks[cz * m_chunkSize + cx].getBlock(rx, y, rz);
}

void MapFinite::setBlock(int x, int y, int z, Block block)
{
	if (outOfBounds(x, z) || z >= BlockHeight || z < 0)
	{
		return;
	}

	int cx = x / ChunkLength;
	int cz = z / ChunkLength;

	int rx = x % ChunkLength;
	int rz = z % ChunkLength;

	m_chunks[cz * m_chunkSize + cx].setBlock(rx, y, rz, block);
}

void MapFinite::update(MasterRenderer& renderer)
{

}

bool MapFinite::outOfBounds(int x, int z) const
{
	if (x < 0 || x >= m_blockSize)
		return true;
	if (z < 0 || z >= m_blockSize)
		return true;

	return false;
}
