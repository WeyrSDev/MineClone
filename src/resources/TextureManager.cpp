#include "TextureManager.hpp"

TextureManager& TextureManager::get()
{
	static TextureManager rm;

	return rm;
}

const Texture* TextureManager::getTexture(std::string src)
{
	auto it = m_textures.find(src);
	if (it == m_textures.end())
	{
		m_textures.insert(std::make_pair(src, Texture(src)));
		
		it = m_textures.find(src);
		
	}

	return &(it->second);
}
