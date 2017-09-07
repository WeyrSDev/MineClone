#pragma once

#include<stack>
#include<memory>

#include<GL/glew.h>
#include<SFML/Window.hpp>

#include "scenes/SceneBase.hpp"

class Game {
public:
	Game();
	~Game();

	void run();

	void pushScene(std::unique_ptr<SceneBase> scene);
	void popScene();

	const sf::Window& getWindow() const { return m_window; };
private:
	void update();
	void draw();

	void handleEvents();

	bool m_running = true;

	sf::Window m_window;
	sf::Clock m_clock;

	std::stack<std::unique_ptr<SceneBase>> m_scenes;
};
