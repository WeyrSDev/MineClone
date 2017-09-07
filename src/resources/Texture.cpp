#include "Texture.hpp"

#include <stdexcept>

#include "util/FilePaths.hpp"

Texture::Texture(std::string src)
{
	if (!m_texture.loadFromFile(texturesPath + src))
	{
		throw std::invalid_argument("Cannot find file: " + std::string(texturesPath) + src);
	}

	bind();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	unBind();

}

void Texture::bind() const
{
	sf::Texture::bind(&m_texture, sf::Texture::CoordinateType::Normalized);
}

void Texture::unBind() const
{
	sf::Texture::bind(0, sf::Texture::CoordinateType::Normalized);
}
