#include "SkyboxRenderer.hpp"

#include <stdio.h>

std::vector<VertexData> skyboxVertexArray() {
	return { genVertexData(-1, 1, 0, 1, 0.25, 1.f / 3.f), //Top left corner
		genVertexData(1, 1, 0, 1, 0.5, 1.f / 3.f), //Top right corner
		genVertexData(1, -1, 0, 1, 0.5, 2.f / 3.f), //Bottom right corner
		genVertexData(-1, -1, 0, 1, 0.25, 2.f / 3.f) }; //Bottom left corner
};

std::vector<GLuint> skyboxIndices()
{
	return { 0, 1, 2, 3, 2, 0};
}

SkyboxRenderer::SkyboxRenderer()
{
	glActiveTexture(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

	m_texture = TextureManager::get().getTexture("skybox.png");

	m_skybox.create(skyboxVertexArray(), skyboxIndices());
	m_shader.create("basic_vertex.glsl", "basic_fragment.glsl");
}

void SkyboxRenderer::render()
{
	m_texture->bind();

	m_shader.bind();
	m_skybox.bind();

	glDrawElements(GL_TRIANGLES, m_skybox.getIndicesCount(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	m_texture->unBind();
}
