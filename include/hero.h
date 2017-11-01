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
public:
	explicit Hero(b2World&, Type type, const TextureManager& textures, sf::Vector2f spawnPoint);
	virtual void drawCurrent(sf::RenderTarget&, sf::RenderStates) const;

	unsigned int getCategory() const;
};

#endif // !MONSTER_H
