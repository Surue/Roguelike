#include "..\include\Hero.h"

#include <utility.h>
#include <iostream>

Textures::ID toTextureID(Hero::Type type) {
	switch (type) {
	case Hero::Warrior:
		return Textures::Warrior;
	}
}

Hero::Hero(b2World& world, Type type, const TextureManager & textures, sf::Vector2f spawnPoint) : m_type(type) {
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

	m_body->CreateFixture(&box);
}

void Hero::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const {
	target.draw(m_sprite, states);
}

unsigned int Hero::getCategory() const {
	return Category::HERO;
}
