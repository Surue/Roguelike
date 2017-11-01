#include "..\include\monster.h"

#include "utility.h"
#include <iostream>

Textures::ID toTextureID(Monster::Type type) {
	switch (type) {
	case Monster::Bones:
		return Textures::Bones;
	case Monster::Archer:
		return Textures::Archer;
	}
}

Monster::Monster(b2World& world, Type type, const TextureManager& textures, sf::Vector2f spawnPoint) : m_type(type){
	m_sprite.setTexture(textures.get(toTextureID(type)));
	//On place l'origine du sprite au centre
	sf::FloatRect bounds = m_sprite.getLocalBounds();
	m_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	//Create the body
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.position = pixel2meter(spawnPoint);
	myBodyDef.fixedRotation = true;
	m_body = world.CreateBody(&myBodyDef);

	//Create the fixtures
	b2FixtureDef box;
	b2PolygonShape box_shape;
	box_shape.SetAsBox(pixel2meter(64.f) / 2.f, pixel2meter(64.f) / 2.f);
	box.shape = &box_shape;
	box.friction = 2.f;

	m_body->CreateFixture(&box);
}

void Monster::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const {
	std::cout << "m_sprite.x " << m_sprite.getPosition().x << "\n";
	std::cout << "m_sprite.y " << m_sprite.getPosition().y << "\n";

	std::cout << "m_body.x " << meter2pixel(m_body->GetPosition().x) << "\n";
	std::cout << "m_body.y " << meter2pixel(m_body->GetPosition().y) << "\n";
	target.draw(m_sprite, states);
}

unsigned int Monster::getCategory() const {
	return Category::MONSTER;
}
