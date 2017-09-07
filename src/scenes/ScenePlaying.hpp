#pragma once

#include <GL/glew.h>

#include"SceneBase.hpp"
#include "renderer/SkyboxRenderer.hpp"

class ScenePlaying : public SceneBase {
public:
	ScenePlaying(const Game& game);

	void update(float delta);
	void render();
	void keyDown(sf::Event::KeyEvent key);
private:
	SkyboxRenderer renderer;
};
