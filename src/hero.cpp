#include "..\include\Hero.h"

Textures::ID toTextureID(Hero::Type type) {
	switch (type) {
	case Hero::Warrior:
		return Textures::Warrior;
	}
}

Hero::Hero(Type type, const TextureManager & textures) : m_type(type), m_sprite(textures.get(toTextureID(type))) {

	//On place l'origine du sprite au centre
	sf::FloatRect bounds = m_sprite.getLocalBounds();
	m_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f); 
}

void Hero::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const {
	target.draw(m_sprite, states);
}

unsigned int Hero::getCategory() const {
	return Category::HERO;
}
