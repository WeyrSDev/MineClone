#include "MapInfinite.hpp"

ChunkId::ChunkId(sf::Int32 _x, sf::Int32 _z)
{
	x = _x;
	z = _z;
}

ChunkId::operator ChunkKey ()
{
	sf::Int32 arr[2] = {x, z};

	return *((sf::Int64*) arr);
}

MapInfinite::MapInfinite(unsigned int seed, const Camera& camera):
	m_generator(seed), m_quit(false),
	m_renderDistance(16), m_camera(camera)
{
	for (int z = -5; z < 5; z++)
	{
		for (int x = -5; x < 5; x++)
		{
			createChunk(x, z);
		}
	}
	
	for (int i = 0; i < 1; i++)
		m_threads.push_back(std::thread(&MapInfinite::loadThread, this));
}

MapInfinite::~MapInfinite()
{
	m_quit = true;
	for (auto& thread : m_threads)
		thread.join();
}

void MapInfinite::update(MasterRenderer& renderer)
{
	m_mutex.lock();
	std::vector<ChunkKey> chunksToDelete;
	for (auto& chunk : m_chunks)
	{
		auto camPos = getChunkPosition(m_camera.position.x, m_camera.position.z);
		auto chunkPos = chunk.second.getPosition();

		int deltaX = camPos.x -  chunkPos.x;
		int deltaZ = camPos.z -  chunkPos.y;
		
		if (deltaX < 0) deltaX = -deltaX;
		if (deltaZ < 0) deltaZ = -deltaZ;
		
		if (deltaX > m_renderDistance || deltaZ > m_renderDistance)
		{
			chunksToDelete.push_back(chunk.first);
			continue;
		}
		chunk.second.update(renderer);
	}

	for (auto key : chunksToDelete)
	{
		m_chunks.erase(key);
	}
	m_mutex.unlock();
}

void MapInfinite::loadThread()
{
	//std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
	while(!m_quit)
	{

		auto camPos = getChunkPosition(m_camera.position.x, m_camera.position.z);

		for (int i = 0; i <= m_renderDistance; i++)
		{
			int left = camPos.x - i;
			int right = camPos.x + i;
			int top = camPos.z - i;
			int bottom = camPos.z + i;
			
			auto newCamPos = getChunkPosition(m_camera.position.x, m_camera.position.z);
			if (newCamPos.x != camPos.x || newCamPos.z != camPos.z)
				break;


			for (int z = top; z <= bottom; z++)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
				m_mutex.lock();
				createChunk(left, z);					
				m_mutex.unlock();

				std::this_thread::sleep_for(std::chrono::milliseconds(1));
				m_mutex.lock();
				createChunk(right, z);					
				m_mutex.unlock();
			}

			for (int x = left; x <= right; x++)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
				m_mutex.lock();
				createChunk(x, top);					
				m_mutex.unlock();

				std::this_thread::sleep_for(std::chrono::milliseconds(1));
				m_mutex.lock();
				createChunk(x, bottom);					
				m_mutex.unlock();
			}
		}
	}
}

Block MapInfinite::getBlock(int x, int y, int z) const
{
	if (y >= BlockHeight)
	{
		return 0;
	}

	auto chunkPos = getChunkPosition(x, z);
	auto chunk = getChunk(chunkPos.x, chunkPos.z);
	if (!chunk || y < 0)
	{
		return 1;
	}

	auto r = toChunkRelativePosition(x, y, z);

	return chunk->getBlock(r.x, r.y, r.z);
}

void MapInfinite::setBlock(int x, int y, int z, Block block)
{
	auto chunkPos = getChunkPosition(x, z);
	auto chunk = getChunk(chunkPos.x, chunkPos.z);
	if (!chunk)
	{
		return;
	}

	auto r = toChunkRelativePosition(x, y, z);

	chunk->setBlock(r.x, r.y, r.z, block);
}

Chunk* MapInfinite::getChunk(int x, int z) const
{
	m_secondMutex.lock();

	auto it = m_chunks.find(ChunkId(x, z));

	if (it == m_chunks.end())
	{
		m_secondMutex.unlock();
		return 0;
	}

	m_secondMutex.unlock();

	return &(it->second);
}

void MapInfinite::createChunk(int x, int z)
{
	if (getChunk(x, z) == 0)
	{
		m_secondMutex.lock();

		ChunkId id(x, z);

		m_chunks.emplace(id, Chunk(Vec2(x, z), this)); 
		m_secondMutex.unlock();
		m_generator.generateChunk(m_chunks.find(id)->second);
	}
}

ChunkId MapInfinite::getChunkPosition(int x, int z) const
{
	int xRes = x / ChunkLength;
	int zRes = z / ChunkLength;

	if (x < 0 && x % ChunkLength != 0) xRes--;
	if (z < 0 && z % ChunkLength != 0) zRes--;

	return ChunkId(xRes, zRes);
}

Vec3 MapInfinite::toChunkRelativePosition(int x, int y, int z) const
{
	x %= ChunkLength;
	if (x < 0) x += ChunkLength;
	z %= ChunkLength;
	if (z < 0) z += ChunkLength;

	return Vec3(x, y, z);
}
