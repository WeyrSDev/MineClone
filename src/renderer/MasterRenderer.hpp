#pragma once
#include "SkyboxRenderer.hpp"

#include <memory>

#include "Camera.hpp"

class MasterRenderer
{
public:
	MasterRenderer();

	void render(const Camera& camera);
private:
	std::unique_ptr<SkyboxRenderer> m_skybox;
};
