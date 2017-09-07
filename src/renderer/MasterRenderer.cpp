#include "MasterRenderer.hpp"

MasterRenderer::MasterRenderer()
{
	glActiveTexture(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

	m_skybox = std::make_unique<SkyboxRenderer>();
}

void MasterRenderer::render(const Camera& camera)
{
	glm::mat4 projectionMatrix = getProjectionMatrix(camera);
	glm::mat4 viewMatrix = getViewMatrix(camera);

	glm::mat4 proViewMatrix = projectionMatrix * viewMatrix;

	glm::mat4 matSkybox = projectionMatrix * getSkyboxViewMatrix(camera);
	m_skybox->render(matSkybox);
}
