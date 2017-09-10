#pragma once
#include "SkyboxRenderer.hpp"
#include "ChunkRenderer.hpp"

#include <memory>

#include "Camera.hpp"

class MasterRenderer
{
public:
	MasterRenderer();

	void addChunk(const ChunkSection& chunk);
	void render(const Camera& camera);
private:
	std::unique_ptr<SkyboxRenderer> m_skybox;
	std::unique_ptr<ChunkRenderer> m_chunk;

	Shader m_shader;
};
