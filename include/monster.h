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
	sf::Sprite m_sprite;
public:
	explicit Monster(Type type, const TextureManager& textures);
	virtual void drawCurrent(sf::RenderTarget&, sf::RenderStates) const;

	unsigned int getCategory() const;
};

#endif // !MONSTER_H
