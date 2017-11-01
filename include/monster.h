#ifndef MONSTER_H
#define MOSNTER_H

#include "entity.h"

class Monster : public Entity {
public:
	enum Type {
		Archer,
		Bones,
	};
private:
	Type m_type;
public:
	explicit Monster(b2World& world, Type type, const TextureManager& textures, sf::Vector2f spawnPoint);
	virtual void drawCurrent(sf::RenderTarget&, sf::RenderStates) const;

	unsigned int getCategory() const;
};

#endif // !MONSTER_H
