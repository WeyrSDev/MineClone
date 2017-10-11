#include "Player.hpp"

#include "map/Functions.hpp"
#include "util/RayCast.hpp"
#include "Game.hpp"

Player::Player(Vec3 position, MapBase* map, const Game* const game):
	m_collbox(position, Vec3(0.8, 1.8, 0.8)), m_camPos(0.4, 1.6, 0.4), m_map(map), m_game(game)
{

}


void Player::update(float delta)
{

	updateMouse(delta);
	updateKeyboard(delta);

	//m_collbox.pos = m_collbox.pos + m_velocity;
	
	move(Vec3(m_velocity.x, 0, 0));
	move(Vec3(0, 0, m_velocity.z));
	move(Vec3(0, m_velocity.y, 0));
	
	m_velocity = m_velocity * 0.0f;
}

void Player::updateMouse(float delta)
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


	static float counter = 0;
	if (counter >= 0)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			counter = -0.1;
			breakBlock();
		}
	}
	else
	{
		counter += delta;
	}
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
	camera.position = m_collbox.pos + m_camPos;
	camera.rotation = m_rotation;
	camera.aspectRatio = (float) m_game->getWindow().getSize().x / m_game->getWindow().getSize().y;

	return camera;
}

void Player::setPosition(Vec3 pos)
{
	m_collbox.pos = pos;
}

const AABB& Player::getCollbox()
{
	return m_collbox;
}

void Player::breakBlock()
{
	RayCast ray(m_rotation, m_collbox.pos + m_camPos);

	for (float s = 0; s < 3; s += 0.01)
	{
		Vec3 pos = ray.step(0.01);
		Vec3 blockPos = getBlockFromPoint(pos);

		Block block = m_map->getBlock(blockPos.x, blockPos.y, blockPos.z);
		if (block.getData().collidable)
		{
			m_map->setBlock(blockPos.x, blockPos.y, blockPos.z, 0);
			break;
		}
	}
}

void Player::pushBlock(BlockId id)
{

}

void Player::move(Vec3 delta)
{
	Vec3 newPos = m_collbox.pos + delta;
	Vec3 c1 = getBlockFromPoint(newPos);
	Vec3 c2 = getBlockFromPoint(newPos + m_collbox.size);

	for(int x = c1.x; x <= c2.x; x++)
	for(int z = c1.z; z <= c2.z; z++)
	for(int y = c1.y; y <= c2.y; y++)
	{
		Block block = m_map->getBlock(x, y, z);
		const BlockData& data = block.getData();

		if (!data.collidable)
		{
			continue;
		}

		AABB newCollbox = m_collbox;
		newCollbox.pos = newPos;
		AABB blockCollbox = data.collbox;
		blockCollbox.pos = Vec3(x, y, z);
		if (!newCollbox.collide(blockCollbox) || m_collbox.collide(blockCollbox))
		{
			continue;
		}

		if (delta.x > 0)
		{
			newPos.x = x - m_collbox.size.x;
		}
		else if (delta.x < 0)
		{
			newPos.x = x + 1;
		}
		if (delta.y > 0)
		{
			newPos.y = y - m_collbox.size.y;
		} 
		else if (delta.y < 0)
		{
			newPos.y = y + 1;
		}
		if (delta.z > 0)
		{
			newPos.z = z - m_collbox.size.z;
		} 
		else if (delta.z < 0)
		{
			newPos.z = z + 1;
		}
	}
	m_collbox.pos = newPos;
}
