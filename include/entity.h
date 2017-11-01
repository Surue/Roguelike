#ifndef ENTITY_H
#define ENTITY_H

#include <Box2D\Box2D.h>

#include "sceneNode.h"
#include "textureManager.h"

class Entity : public SceneNode {
protected:
	b2Body* m_body;
	sf::Sprite m_sprite;
public:
	void setLinearVelocity(sf::Vector2f);
	void setLinearVelocity(b2Vec2);
	b2Vec2 getLinearVelocity() const;
private:
	virtual void updateCurrent(sf::Time);
};
#endif // !ENTITY_H
