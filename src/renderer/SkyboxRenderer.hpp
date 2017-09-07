#pragma once

#include <memory>

#include "util/Matrices.hpp"
#include "shader/Shader.hpp"
#include "Mesh.hpp"
#include "resources/TextureManager.hpp"

constexpr float skyboxSize = 1000.f;
class SkyboxRenderer {
public:
	SkyboxRenderer();

	void render(glm::mat4& transform);
private:
	Mesh m_skybox;
	Shader m_shader;

	const Texture* m_texture;
};
