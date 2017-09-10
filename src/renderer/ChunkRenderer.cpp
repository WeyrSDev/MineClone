#include "ChunkRenderer.hpp"

ChunkRenderer::ChunkRenderer()
{
	m_texture = TextureManager::get().getTexture("atlas.png");
}

void ChunkRenderer::addChunk(const ChunkSection& chunk)
{
	m_visibleChunks.push_back(&chunk);

}

void ChunkRenderer::render()
{
	m_texture->bind();
	for (auto chunk : m_visibleChunks)
	{
		const Mesh* mesh = chunk->getMesh();

		mesh->bind();

		glDrawElements(GL_TRIANGLES, mesh->getIndicesCount(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);


	}
	m_visibleChunks.clear();
}
