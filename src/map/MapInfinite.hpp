#pragma once

#include <unordered_map>
#include <thread>
#include <atomic>
#include <mutex>

#include "MapBase.hpp"
#include "generator/WorldGenerator.hpp"

class MapInfinite : public MapBase {
public:
	MapInfinite(unsigned int seed, const Camera& camera);
	~MapInfinite();

	void spawnPlayer(Vec2 pos, Player& player);

	void update(MasterRenderer& renderer);

	Block getBlock(int x, int y, int z) const;
	void setBlock(int x, int y, int z, Block block);

	Chunk* getChunk(int x, int z) const;
private:
	const Camera& m_camera;

	void createChunk(int x, int z);

	void loadThread();

	mutable std::unordered_map<ChunkKey, Chunk> m_chunks;

	WorldGenerator m_generator;

	std::vector<std::thread> m_threads;
	std::mutex m_mutex;
	mutable std::mutex m_secondMutex;
	std::atomic<bool> m_quit;
	const unsigned int m_renderDistance;
};
