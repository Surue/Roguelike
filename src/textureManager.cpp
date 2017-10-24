#include "..\include\textureManager.h"

#include <assert.h>

void TextureManager::load(Textures::ID id, const std::string & filename) {
	std::unique_ptr<sf::Texture> texture(new sf::Texture());
	if (!texture->loadFromFile(filename)) {
		throw std::runtime_error("TextureManager::load - Failed to load " + filename);
	}

	auto inserted = m_textureMap.insert(std::make_pair(id, std::move(texture)));
	assert(inserted.second);
}

sf::Texture & TextureManager::get(Textures::ID id) {
	auto found = m_textureMap.find(id);
	assert(found != m_textureMap.end());

	return *found->second;
}

const sf::Texture & TextureManager::get(Textures::ID id) const {
	auto found = m_textureMap.find(id);
	assert(found != m_textureMap.end());

	return *found->second;
}
