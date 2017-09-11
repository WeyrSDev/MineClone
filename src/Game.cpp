#include "Game.hpp"
#include "map/data/Block.hpp"

Game::Game() 
{
	printf("%d\n", sizeof(Block));
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.majorVersion = 3.3;
	settings.minorVersion = 3.3;

	m_window.create(sf::VideoMode(800, 600), "OpenBlocks", sf::Style::Default, settings);
	glewInit();
}

Game::~Game() 
{

}

void Game::run() 
{
	m_window.setActive(true);

	m_window.setFramerateLimit(200);

	m_clock.restart();
	while(m_running && !m_scenes.empty()) 
	{
		handleEvents();

		update();
		draw();
		
	}
}

void Game::update()
{
	sf::Time delta = m_clock.restart();

	if (!m_scenes.empty())
		m_scenes.top()->update(delta.asSeconds());
}

void Game::draw() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (!m_scenes.empty())
		m_scenes.top()->render();

	m_window.display();
}

void Game::handleEvents() 
{
	sf::Event event;

	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				m_running = false;
				break;
			case sf::Event::KeyPressed:
				if (!m_scenes.empty())
				{
					m_scenes.top()->keyDown(event.key);
				}
				break;
			case sf::Event::Resized:
				glViewport(0, 0, event.size.width, event.size.height);
				break;
		}
	}
}


void Game::pushScene(std::unique_ptr<SceneBase> scene)
{
	m_scenes.push(std::move(scene));
}

void Game::popScene()
{
	m_scenes.pop();
}
