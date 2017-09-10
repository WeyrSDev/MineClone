#include "ScenePlaying.hpp"

#include "Game.hpp"
#include "map/MapFinite.hpp"

ScenePlaying::ScenePlaying(const Game& game) :
	SceneBase(game), m_camera({{0, 0, 0}, {0, 0, 0}, 0}),
	m_pause(0)
{
	int centerX = m_game->getWindow().getSize().x / 2;
	int centerY = m_game->getWindow().getSize().y / 2;
	
	sf::Mouse::setPosition(sf::Vector2i(centerX, centerY), m_game->getWindow());

	m_map = std::make_unique<MapFinite>(8);
}

void ScenePlaying::update(float delta)
{
	m_camera.aspectRatio = float(m_game->getWindow().getSize().x) / m_game->getWindow().getSize().y;

	if (m_pause)
	{
		return;
	}

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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_camera.position.z += delta * 4;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_camera.position.z -= delta * 4;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_camera.position.x -= delta * 4;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_camera.position.x += delta * 4;
	}

	m_map->update(m_renderer);
}

void ScenePlaying::render()
{
	m_renderer.render(m_camera);
}

void ScenePlaying::keyDown(sf::Event::KeyEvent key)
{
	if (key.code == sf::Keyboard::Escape)
	{
		m_pause = !m_pause;
	}
}
