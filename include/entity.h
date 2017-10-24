#ifndef ENTITY_H
#define ENTITY_H

#include "sceneNode.h"
#include "textureManager.h"

class Entity : public SceneNode {
private:
	sf::Vector2f m_velocity;
public:
	void setVelocity(sf::Vector2f);
	void setVelocity(float, float);
	sf::Vector2f getVelocity() const;
private:
	virtual void updateCurrent(sf::Time);
};
#endif // !ENTITY_H
