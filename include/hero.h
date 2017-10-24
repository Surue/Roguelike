#ifndef HERO_H
#define HERO_H

#include "entity.h"

class Hero : public Entity {
public:
	enum Type {
		Warrior
	};
private:
	Type m_type;
	sf::Sprite m_sprite;
public:
	explicit Hero(Type type, const TextureManager& textures);
	virtual void drawCurrent(sf::RenderTarget&, sf::RenderStates) const;

	unsigned int getCategory() const;
};

#endif // !MONSTER_H
