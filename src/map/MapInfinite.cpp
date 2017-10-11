#include "MapInfinite.hpp"

#include "player/Player.hpp"
#include "Functions.hpp"
#include "data/BlockDataBase.hpp"

MapInfinite::MapInfinite(unsigned int seed, const Camera& camera):
	m_generator(seed), m_quit(false),
	m_renderDistance(16), m_camera(camera)
{
	for (int i = 0; i < 1; i++)
		m_threads.push_back(std::thread(&MapInfinite::loadThread, this));
}

MapInfinite::~MapInfinite()
{
	m_quit = true;
	for (auto& thread : m_threads)
		thread.join();
}

void MapInfinite::spawnPlayer(Vec2 pos, Player& player)
{
	float playerHeight = player.getCollbox().size.y;
	int cx = pos.x;
	int cz = pos.y;

	m_mutex.lock();
	for (int z = cz - 2; z < cz + 3; z++)
	{
		for (int x = cx - 2; x < cx + 3; x++)
		{
			createChunk(x, z);
		}
	}

	for (int y = BlockHeight; y > 1; y--)
	{
		if (getBlock(cx, y, cz).getData().collidable)
		{
			player.setPosition(Vec3(cx, y + playerHeight, cz));
			break;
		}
	}
	m_mutex.unlock();
}

void MapInfinite::update(MasterRenderer& renderer)
{
	m_mutex.lock();
	std::vector<ChunkKey> chunksToDelete;
	for (auto& chunk : m_chunks)
	{
		auto camPos = getChunkFromBlock(m_camera.position.x, m_camera.position.z);
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

		auto camPos = getChunkFromBlock(m_camera.position.x, m_camera.position.z);

		for (int i = 0; i <= m_renderDistance; i++)
		{
			int sleepFor = 1;
			if (i > 3)
			{
				sleepFor = 3;
			}
			if (i > 5)
			{
				sleepFor = 4;
			}
			if (i > 9)
			{
				sleepFor = 5;
			}

			int left = camPos.x - i;
			int right = camPos.x + i;
			int top = camPos.z - i;
			int bottom = camPos.z + i;
			


			for (int z = top; z <= bottom; z++)
			{
				auto newCamPos = getChunkFromBlock(m_camera.position.x, m_camera.position.z);
				if (newCamPos.x != camPos.x || newCamPos.z != camPos.z)
					break;
				std::this_thread::sleep_for(std::chrono::milliseconds(sleepFor));
				m_mutex.lock();
				createChunk(left, z);					
				m_mutex.unlock();

				std::this_thread::sleep_for(std::chrono::milliseconds(sleepFor));
				m_mutex.lock();
				createChunk(right, z);					
				m_mutex.unlock();
			}

			for (int x = left; x <= right; x++)
			{
				auto newCamPos = getChunkFromBlock(m_camera.position.x, m_camera.position.z);
				if (newCamPos.x != camPos.x || newCamPos.z != camPos.z)
					break;
				std::this_thread::sleep_for(std::chrono::milliseconds(sleepFor));
				m_mutex.lock();
				createChunk(x, top);					
				m_mutex.unlock();

				std::this_thread::sleep_for(std::chrono::milliseconds(sleepFor));
				m_mutex.lock();
				createChunk(x, bottom);					
				m_mutex.unlock();
			}
			auto newCamPos = getChunkFromBlock(m_camera.position.x, m_camera.position.z);
			if (newCamPos.x != camPos.x || newCamPos.z != camPos.z)
				break;
		}
	}
}

Block MapInfinite::getBlock(int x, int y, int z) const
{
	if (y >= BlockHeight)
	{
		return 0;
	}

	auto chunkPos = getChunkFromBlock(x, z);
	auto chunk = getChunk(chunkPos.x, chunkPos.z);
	if (!chunk || y < 0)
	{
		return (BlockId) BlocksIds::stone;
	}

	auto r = toChunkRelativePosition(x, y, z);

	return chunk->getBlock(r.x, r.y, r.z);
}

void MapInfinite::setBlock(int x, int y, int z, Block block)
{
	if (y <= 0 || y >= BlockHeight)
	{
		return;
	}
	auto chunkPos = getChunkFromBlock(x, z);
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
