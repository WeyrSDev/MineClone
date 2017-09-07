#include "ScenePlaying.hpp"

#include "Game.hpp"

ScenePlaying::ScenePlaying(const Game& game) :
	SceneBase(game), m_camera({{0, 0, 0}, {0, 0, 0}, 0})
{
}

void ScenePlaying::update(float delta)
{
	m_camera.aspectRatio = float(m_game->getWindow().getSize().x) / m_game->getWindow().getSize().y;

	int centerX = m_game->getWindow().getSize().x / 2;
	int centerY = m_game->getWindow().getSize().y / 2;

	int deltaX = sf::Mouse::getPosition(m_game->getWindow()).x - centerX;
	int deltaY = sf::Mouse::getPosition(m_game->getWindow()).y - centerY;

	sf::Mouse::setPosition(sf::Vector2i(centerX, centerY), m_game->getWindow());
	
	m_camera.rotation.y += deltaX;
	if (m_camera.rotation.y > 360)
		m_camera.rotation.y -= 360;
	if (m_camera.rotation.y < 0)
		m_camera.rotation.y += 360;

	m_camera.rotation.x += deltaY;

	if (m_camera.rotation.x < -80)
		m_camera.rotation.x = -80;
	if (m_camera.rotation.x > 80)
		m_camera.rotation.x = 80;
}

void ScenePlaying::render()
{
	m_renderer.render(m_camera);
}

void ScenePlaying::keyDown(sf::Event::KeyEvent key)
{
}
