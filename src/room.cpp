#include "..\include\room.h"
#include <iostream>
#include "textureManager.h"
#include "utility.h"

Textures::ID toTextureID(Tile::Type type) {
	switch (type) {
	case Tile::WALL:
		return Textures::Wall;
	case Tile::GROUND:
		return Textures::Ground;
	}
}

Tile::Tile(b2World& world, int x, int y, int type, const TextureManager& textures) {
	caseCoord.x = x;
	caseCoord.y = y;
	m_type = static_cast<Type>(type);
	m_sprite.setTexture(textures.get(toTextureID(m_type)));

	sf::FloatRect bounds = m_sprite.getLocalBounds();
	m_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	if (m_type == Tile::WALL || m_type == Tile::PILLAR) {
		//Create the body
		b2BodyDef myBodyDef;
		myBodyDef.type = b2_staticBody;
		myBodyDef.position = pixel2meter(Room::caseCoord2pixels(caseCoord));
		myBodyDef.fixedRotation = true;
		m_body = world.CreateBody(&myBodyDef);

		//Create the fixtures
		b2FixtureDef box;
		b2PolygonShape box_shape;
		box_shape.SetAsBox(pixel2meter(64.f) / 2.f, pixel2meter(64.f) / 2.f);
		box.shape = &box_shape;

		m_body->CreateFixture(&box);
	}else {

	}
}

Tile::~Tile() {
}

void Tile::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const {
	target.draw(m_sprite, states);
}

Room::Room() {
}

void Room::build(b2World& world, std::vector<std::vector<int>>& roomTiles, const TextureManager& textures) {
	for (int i = 0; i < roomTiles.size(); i++) {
		for (int j = 0; j < roomTiles.at(i).size(); j++) {
			std::unique_ptr<Tile> tmpTile(new Tile(world, i, j, roomTiles.at(i).at(j), textures));
			Tile* tile = tmpTile.get();
			CaseCoord coord;
			coord.x = i;
			coord.y = j;
			tile->setPosition(caseCoord2pixels(coord));
			this->attachChild(std::move(tmpTile));
		}
	}
}

sf::Vector2f Room::caseCoord2pixels(CaseCoord caseCoord) {
	return sf::Vector2f(caseCoord.x / (SCALE), caseCoord.y / (SCALE));
}

CaseCoord Room::pixels2caseCoord(sf::Vector2f vect) {
	CaseCoord caseCoord;
	caseCoord.x = vect.x * SCALE;
	caseCoord.y = vect.y * SCALE;
	return caseCoord;
}
