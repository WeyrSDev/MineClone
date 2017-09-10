#pragma once

#include "resources/TextureManager.hpp"
#include "util/Matrices.hpp"
#include "map/chunk/ChunkSection.hpp"

class ChunkRenderer {
public:
	ChunkRenderer();
	void addChunk(const ChunkSection& chunk);

	void render();
private:
	std::vector<const ChunkSection*> m_visibleChunks;
	const Texture* m_texture;
};
