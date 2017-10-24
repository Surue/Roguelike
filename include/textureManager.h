#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <map>
#include <string>
#include <memory>
#include <SFML\Graphics.hpp>

namespace Textures {
	enum ID {
		Warrior,
		Archer,
		Bones,
		Cobble
	};
}

class TextureManager {
private:
	std::map<Textures::ID, std::unique_ptr<sf::Texture>> m_textureMap;
public:
	void load(Textures::ID, const std::string&);
	sf::Texture& get(Textures::ID);
	const sf::Texture& get(Textures::ID) const;
};

#endif // !TEXTURE_MANAGER_H
