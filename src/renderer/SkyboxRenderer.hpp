#pragma once

#include <memory>

#include "shader/Shader.hpp"
#include "Mesh.h"
#include "resources/TextureManager.hpp"

class SkyboxRenderer {
public:
	SkyboxRenderer();

	void render();
private:
	std::shared_ptr<Mesh> m_skybox;
	std::shared_ptr<Shader> m_shader;

	const Texture* m_texture;
};
