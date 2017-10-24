#include "..\include\monster.h"

Textures::ID toTextureID(Monster::Type type) {
	switch (type) {
	case Monster::Bones:
		return Textures::Bones;
	case Monster::Archer:
		return Textures::Archer;
	}
}

Monster::Monster(Type type, const TextureManager& textures) : m_type(type), m_sprite(textures.get(toTextureID(type))) {

	//On place l'origine du sprite au centre
	sf::FloatRect bounds = m_sprite.getLocalBounds();
	m_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Monster::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const {
	target.draw(m_sprite, states);
}

unsigned int Monster::getCategory() const {
	return Category::MONSTER;
}
