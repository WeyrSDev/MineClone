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
	Mesh m_skybox;
	Shader m_shader;

	const Texture* m_texture;
};
