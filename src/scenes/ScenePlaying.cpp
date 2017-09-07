#include "ScenePlaying.hpp"

ScenePlaying::ScenePlaying(const Game& game) :
	SceneBase(game)
{
}

void ScenePlaying::update(float delta)
{
}

void ScenePlaying::render()
{
	renderer.render();
}

void ScenePlaying::keyDown(sf::Event::KeyEvent key)
{
}
