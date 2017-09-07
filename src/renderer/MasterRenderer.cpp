#include "MasterRenderer.hpp"

MasterRenderer::MasterRenderer()
{
	glActiveTexture(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

	m_skybox = std::make_unique<SkyboxRenderer>();
}

void MasterRenderer::render(const Camera& camera)
{
	glm::mat4 view, projection, matSkybox;

	projection = glm::perspective(glm::radians(90.f), camera.aspectRatio, 0.01f, 2000.f);

	view = glm::rotate(view, glm::radians(camera.rotation.x), {1, 0, 0});
	view = glm::rotate(view, glm::radians(camera.rotation.y), {0, 1, 0});
	view = glm::rotate(view, glm::radians(camera.rotation.z), {0, 0, 1});

	matSkybox = projection * view;

	view = glm::translate(view, -camera.position);


	glm::mat4 projView = projection * view;
	m_skybox->render(matSkybox);
}
