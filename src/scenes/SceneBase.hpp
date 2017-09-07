#pragma once
#include <SFML/Window.hpp>

class Game;

class SceneBase{
public:
	SceneBase(const Game& game) : m_game(&game) {};

	virtual void update(float delta) = 0;
	virtual void render() = 0;
	virtual void keyDown(sf::Event::KeyEvent key) = 0;
protected:
	const Game* const  m_game;
};
