#include "ScenePlaying.hpp"

#include "Game.hpp"

ScenePlaying::ScenePlaying(const Game& game) :
	SceneBase(game), m_camera({{0, 0, 0}, {0, 0, 0}, 0})
{
}

void ScenePlaying::update(float delta)
{
	m_camera.aspectRatio = float(m_game->getWindow().getSize().x) / m_game->getWindow().getSize().y;

	m_camera.rotation.y += delta * 50;
}

void ScenePlaying::render()
{
	m_renderer.render(m_camera);
}

void ScenePlaying::keyDown(sf::Event::KeyEvent key)
{
}
