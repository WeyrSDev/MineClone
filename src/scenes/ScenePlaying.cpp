#include "ScenePlaying.hpp"

#include "Game.hpp"
#include "map/MapFinite.hpp"

Vec3 velocity;

ScenePlaying::ScenePlaying(const Game& game) :
	SceneBase(game), m_camera({{256, 82, 256}, {0, 0, 0}, 0}),
	m_pause(0) 
{
	int centerX = m_game->getWindow().getSize().x / 2;
	int centerY = m_game->getWindow().getSize().y / 2;
	
	sf::Mouse::setPosition(sf::Vector2i(centerX, centerY), m_game->getWindow());

	m_map = std::make_unique<MapFinite>(32);

	velocity = Vec3();
}

void ScenePlaying::update(float delta)
{
	m_camera.aspectRatio = float(m_game->getWindow().getSize().x) / m_game->getWindow().getSize().y;

	if (!m_pause)
	{
		updatePlaying(delta);
	}


	m_map->update(m_renderer);
}

void ScenePlaying::updatePlaying(float delta)
{
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

	float angle = m_camera.rotation.y;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		velocity.x -= glm::cos(glm::radians(angle + 90)) * delta;
		velocity.z -= glm::sin(glm::radians(angle + 90)) * delta;
		velocity.y -= glm::tan(glm::radians(m_camera.rotation.x)) * delta;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		velocity.x += glm::cos(glm::radians(angle + 90)) * delta;
		velocity.z += glm::sin(glm::radians(angle + 90)) * delta;
		velocity.y += glm::tan(glm::radians(m_camera.rotation.x)) * delta;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		velocity.x -= glm::cos(glm::radians(angle)) * delta;
		velocity.z -= glm::sin(glm::radians(angle)) * delta;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		velocity.x += glm::cos(glm::radians(angle)) * delta;
		velocity.z += glm::sin(glm::radians(angle)) * delta;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		velocity.y += delta;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		velocity.y -= delta;
	}
	m_camera.position = m_camera.position + velocity;
	velocity = velocity * 0.95f;
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
