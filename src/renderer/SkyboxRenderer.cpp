#include "SkyboxRenderer.hpp"

#include <stdio.h>

std::vector<VertexData> skyboxVertexArray() {
	return { genVertexData(-1, 1, 0, 1, 0, 0), //Top left corner
		genVertexData(1, 1, 0, 1, 1, 0), //Top right corner
		genVertexData(1, -1, 0, 1, 1, 1), //Bottom right corner
		genVertexData(-1, -1, 0, 1, 0, 1) }; //Bottom left corner
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
