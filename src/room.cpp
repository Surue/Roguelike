#include "..\include\room.h"
#include <iostream>
#include "textureManager.h"

Textures::ID toTextureID(Tile::Type type) {
	switch (type) {
	case Tile::WALL:
		return Textures::Wall;
	case Tile::GROUND:
		return Textures::Ground;
	}
}

Tile::Tile(int x, int y, int type, const TextureManager& textures) {
	caseCoord.x = x;
	caseCoord.y = y;
	m_type = static_cast<Type>(type);
	m_sprite.setTexture(textures.get(toTextureID(m_type)));

	sf::FloatRect bounds = m_sprite.getLocalBounds();
	m_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

Tile::~Tile() {
}

void Tile::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const {
	target.draw(m_sprite, states);
	//std::cout << "x = " << m_sprite.getPosition().x << ", y = " << m_sprite.getPosition().y << "\n";
}

void Room::build(std::vector<std::vector<int>>& roomTiles, const TextureManager& textures) {
	for (int i = 0; i < roomTiles.size(); i++) {
		for (int j = 0; j < roomTiles.at(i).size(); j++) {
			std::unique_ptr<Tile> tmpTile(new Tile(i, j, roomTiles.at(i).at(j), textures));
			Tile* tile = tmpTile.get();
			CaseCoord coord;
			coord.x = i;
			coord.y = j;
			std::cout << "i = " << i << " => x = " << caseCoord2pixels(coord).x << ", j = " << j << " => y = " << caseCoord2pixels(coord).y << "\n";
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
