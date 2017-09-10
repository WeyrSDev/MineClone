#include "MasterRenderer.hpp"

MasterRenderer::MasterRenderer()
{
	glEnable(GL_DEPTH_TEST);
	glActiveTexture(GL_TEXTURE_2D);

	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	m_shader.create("basic_vertex.glsl", "basic_fragment.glsl");

	m_skybox = std::make_unique<SkyboxRenderer>();
	m_chunk = std::make_unique<ChunkRenderer>();
}

void MasterRenderer::addChunk(const ChunkSection& chunk)
{
	m_chunk->addChunk(chunk);
}

void MasterRenderer::render(const Camera& camera)
{
	glm::mat4 projectionMatrix = MatrixUtil::getProjectionMatrix(camera);
	glm::mat4 viewMatrix = MatrixUtil::getViewMatrix(camera);

	glm::mat4 projViewMatrix = projectionMatrix * viewMatrix;

	glm::mat4 matSkybox = projectionMatrix * MatrixUtil::getSkyboxViewMatrix(camera);

	//glEnable(GL_CULL_FACE);

	m_shader.bind();

	m_shader.setTransformMatrix(matSkybox);
	m_skybox->render(matSkybox);

	m_shader.setTransformMatrix(projViewMatrix);
	m_chunk->render();
}
