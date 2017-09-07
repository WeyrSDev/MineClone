#pragma once

#include <string>
#include <GL/glew.h>
#include <SFML/Graphics.hpp>

class Texture {
public:
	Texture(std::string src);

	void operator delete (void*) = delete;

	void bind() const;
	void unBind() const;
private:
	sf::Texture m_texture;
};
