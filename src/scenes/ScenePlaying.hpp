#pragma once
#include"SceneBase.hpp"

#include <GL/glew.h>

#include "renderer/MasterRenderer.hpp"
#include "map/MapBase.hpp"

class ScenePlaying : public SceneBase {
public:
	ScenePlaying(const Game& game);

	void update(float delta);
	void render();
	void keyDown(sf::Event::KeyEvent key);
private:
	MasterRenderer m_renderer;
	Camera m_camera;

	std::unique_ptr<MapBase> m_map;
	bool m_pause;
};
