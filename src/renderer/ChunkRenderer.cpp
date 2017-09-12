#include "ChunkRenderer.hpp"

ChunkRenderer::ChunkRenderer()
{
	m_texture = TextureManager::get().getTexture("atlas.png");
}

void ChunkRenderer::addChunk(const ChunkSection& chunk)
{
	auto& meshes = chunk.getMeshes();

	if (meshes.liquid.getIndicesCount() > 0)
	{
		m_liquidMeshes.push_back(&meshes.liquid);
	}

	if (meshes.solid.getIndicesCount() > 0)
	{
		m_solidMeshes.push_back(&meshes.solid);
	}
}

void ChunkRenderer::renderSolid()
{
	m_texture->bind();
	for (auto mesh : m_solidMeshes)
	{
		mesh->bind();

		glDrawElements(GL_TRIANGLES, mesh->getIndicesCount(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
	m_solidMeshes.clear();
}
void ChunkRenderer::renderLiquid()
{
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	for (auto mesh : m_liquidMeshes)
	{
		mesh->bind();

		glDrawElements(GL_TRIANGLES, mesh->getIndicesCount(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
	m_liquidMeshes.clear();
	glDisable(GL_BLEND);
	glEnable(GL_CULL_FACE);
}
