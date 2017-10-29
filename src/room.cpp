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

Tile::Tile(int x, int y, int type) {
	caseCoord.x = x;
	caseCoord.y = y;
	type = static_cast<Type>(type);
}

Tile::~Tile() {
}

void Room::build(std::vector<std::vector<int>>& roomTiles) {
	for (int i = 0; i < roomTiles.size(); i++) {
		for (int j = 0; j < roomTiles.at(i).size(); j++) {
			std::cout << "case[" << i << ", " << j << "] = " << roomTiles.at(i).at(j) << "\n";
		}
	}
}

sf::Vector2f Room::caseCoord2pixels(CaseCoord caseCoord) {
	return sf::Vector2f(caseCoord.x / SCALE, caseCoord.y / SCALE);
}

CaseCoord Room::pixels2caseCoord(sf::Vector2f vect) {
	CaseCoord caseCoord;
	caseCoord.x = vect.x * SCALE;
	caseCoord.y = vect.y * SCALE;
	return caseCoord;
}
