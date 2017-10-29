#ifndef ROOM_H
#define ROOM_H

#include "sceneNode.h"

struct CaseCoord {
	int x;
	int y;
};

class Tile : public SceneNode{
public:
	enum Type {
		WALL,
		GROUND,
		PILLAR,
		SPAWN,
		ENTRANCE,
		EXIT
	};
private:
	sf::Sprite m_sprite;
	bool isSolid;
	CaseCoord caseCoord;
	Type m_type;
public:
	explicit Tile(int x, int y, int type);
	~Tile();
};

class Room : public SceneNode {
private:
	std::vector<Tile> tiles;
	bool isVisible;
public:
	void build(std::vector<std::vector<int>>& roomTiles);
	sf::Vector2f caseCoord2pixels(CaseCoord);
	CaseCoord pixels2caseCoord(sf::Vector2f);
};

#endif // !ROOM_H
