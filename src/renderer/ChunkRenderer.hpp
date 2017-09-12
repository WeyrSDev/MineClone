#pragma once

#include "resources/TextureManager.hpp"
#include "util/Matrices.hpp"
#include "map/chunk/ChunkSection.hpp"

class ChunkRenderer {
public:
	ChunkRenderer();
	void addChunk(const ChunkSection& chunk);

	void renderSolid();
	void renderLiquid();
private:
	std::vector<const Mesh*> m_solidMeshes, m_liquidMeshes;
	const Texture* m_texture;
};
