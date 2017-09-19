#include "Player.hpp"

#include "Game.hpp"

Player::Player(Vec3 position, MapBase* map, const Game* const game):
	m_position(position), m_map(map), m_game(game)
{

}


void Player::update(float delta)
{

	updateMouse();
	updateKeyboard(delta);

	m_position = m_position + m_velocity;

	m_velocity = m_velocity * 0.0f;

	for (int x = -2; x < 3; x++)
	for (int z = -2; z < 3; z++)
	for (int y = -1; y < 3; y++)
	{
		Vec3 block = m_position + Vec3(x, y, z);

		m_map->setBlock(block.x, block.y, block.z, 0);
	}
}

void Player::updateMouse()
{
	int centerX = m_game->getWindow().getSize().x / 2;
	int centerY = m_game->getWindow().getSize().y / 2;

	int deltaX = sf::Mouse::getPosition(m_game->getWindow()).x - centerX;
	int deltaY = sf::Mouse::getPosition(m_game->getWindow()).y - centerY;
	
	sf::Mouse::setPosition(sf::Vector2i(centerX, centerY), m_game->getWindow());

	m_rotation.y += deltaX;
	if (m_rotation.y > 360)
		m_rotation.y -= 360;
	if (m_rotation.y < 0)
		m_rotation.y += 360;

	m_rotation.x += deltaY;

	if (m_rotation.x < -80)
		m_rotation.x = -80;
	if (m_rotation.x > 80)
		m_rotation.x = 80;
}

void Player::updateKeyboard(float delta)
{
	float speed = 4.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
		speed *= 4;

	float angle = m_rotation.y;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_velocity.x -= glm::cos(glm::radians(angle + 90)) * delta * speed;
		m_velocity.z -= glm::sin(glm::radians(angle + 90)) * delta * speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_velocity.x += glm::cos(glm::radians(angle + 90)) * delta * speed;
		m_velocity.z += glm::sin(glm::radians(angle + 90)) * delta * speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_velocity.x -= glm::cos(glm::radians(angle)) * delta * speed;
		m_velocity.z -= glm::sin(glm::radians(angle)) * delta * speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_velocity.x += glm::cos(glm::radians(angle)) * delta * speed;
		m_velocity.z += glm::sin(glm::radians(angle)) * delta * speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		m_velocity.y += delta * speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		m_velocity.y -= delta * speed;
	}
}

Camera Player::getCam()
{
	Camera camera;
	camera.position = m_position + Vec3(0.4, 1.6, 0.4);
	camera.rotation = m_rotation;
	camera.aspectRatio = (float) m_game->getWindow().getSize().x / m_game->getWindow().getSize().y;

	return camera;
}
