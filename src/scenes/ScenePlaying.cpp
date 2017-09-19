#include "ScenePlaying.hpp"

#include <stdlib.h>
#include <time.h>

#include "Game.hpp"
#include "map/MapFinite.hpp"
#include "map/MapInfinite.hpp"

ScenePlaying::ScenePlaying(const Game& game) :
	SceneBase(game), m_camera({{0, 82, 0}, {0, 0, 0}, 0}),
	m_pause(0) 
{
	srand(time(NULL));

	int centerX = m_game->getWindow().getSize().x / 2;
	int centerY = m_game->getWindow().getSize().y / 2;
	
	sf::Mouse::setPosition(sf::Vector2i(centerX, centerY), m_game->getWindow());

	m_map = std::make_unique<MapInfinite>(rand(), m_camera);
	m_player = std::make_unique<Player>(Vec3(0, 82, 0), m_map.get(), m_game);
}

void ScenePlaying::update(float delta)
{
	if (!m_pause)
	{
		updatePlaying(delta);
	}

	m_camera = m_player->getCam();

	m_map->update(m_renderer);
}

void ScenePlaying::updatePlaying(float delta)
{
	m_player->update(delta);
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
