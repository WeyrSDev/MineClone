#pragma once

#include <SFML/System.hpp>

#include "map/data/BlockDataBase.hpp"
#include "map/MapBase.hpp"
#include "Camera.hpp"

class Game;

class Player {
public:
	Player(Vec3 position, MapBase* map, const Game* const game);

	void update(float delta);
	Camera getCam();

private:
	void updateMouse(float delta);
	void updateKeyboard(float delta);

	void breakBlock();
	void pushBlock(BlockId block);

	MapBase* m_map;
	Vec3 m_velocity;
	Vec3 m_position, m_rotation;
	Vec3 m_camPos;
	const Game* const m_game;
};
