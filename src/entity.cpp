#include "..\include\entity.h"

void Entity::setVelocity(sf::Vector2f velocity) {
	m_velocity = velocity;
}

void Entity::setVelocity(float velX, float velY) {
	m_velocity.x = velX;
	m_velocity.y = velY;
}

sf::Vector2f Entity::getVelocity() const {
	return m_velocity;
}

void Entity::updateCurrent(sf::Time dt) {
	move(m_velocity * dt.asSeconds());
}
