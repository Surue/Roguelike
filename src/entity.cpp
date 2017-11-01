#include "..\include\entity.h"

#include "utility.h"

void Entity::setLinearVelocity(sf::Vector2f vel) {
	m_body->SetLinearVelocity(pixel2meter(vel));
}

void Entity::setLinearVelocity(b2Vec2 vel) {
	m_body->SetLinearVelocity(vel);
}

b2Vec2 Entity::getLinearVelocity() const {
	return m_body->GetLinearVelocity();
}

void Entity::updateCurrent(sf::Time dt) {
	sf::Vector2f center_position = meter2pixel(m_body->GetPosition());
	m_sprite.setPosition(center_position);
}
