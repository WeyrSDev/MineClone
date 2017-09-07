#pragma once

#include <string>
#include <unordered_map>

#include "Texture.hpp"

#include "util/Singleton.hpp"


class TextureManager: public Singleton 
{
public:
	static TextureManager& get();
	static void bindTexture(sf::Texture* txt);

	const Texture* getTexture(std::string src);
	
private:
	TextureManager() {};
	~TextureManager() {};

	std::unordered_map<std::string, Texture> m_textures;
};
