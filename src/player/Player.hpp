#pragma once

#include <SFML/System.hpp>

#include "util/AABB.hpp"
#include "map/data/BlockDataBase.hpp"
#include "map/MapBase.hpp"
#include "Camera.hpp"

class Game;

class Player {
public:
	Player(Vec3 position, MapBase* map, const Game* const game);

	void update(float delta);
	Camera getCam();

	void setPosition(Vec3 pos);
	const AABB& getCollbox();

private:
	void updateMouse(float delta);
	void updateKeyboard(float delta);

	void breakBlock();
	void pushBlock(BlockId block);

	void move(Vec3 delta);

	MapBase* m_map;
	Vec3 m_velocity;
	Vec3 m_rotation;
	Vec3 m_camPos;
	AABB m_collbox;

	const Game* const m_game;
};
