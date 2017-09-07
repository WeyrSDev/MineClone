#include "Game.hpp"
#include "scenes/ScenePlaying.hpp"

int main(int argc, char** argv)
{
	Game game;
	game.pushScene(std::make_unique<ScenePlaying>(game));
	game.run();
}
