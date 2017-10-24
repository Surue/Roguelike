#ifndef GAME_H
#define GAME_H

#include <SFML\Graphics.hpp>
#include <iostream>
#include <functional>
#include "world.h"
#include "player.h"

class Game {
private :
	sf::RenderWindow m_window;
	const sf::Time timePerFrame = sf::seconds(1.f / 60.f);
	World m_world;
	bool isPaused;

	Player m_player;

	void processEvent();
	void update(sf::Time);
	void render();
public:
	Game();
	~Game();

	void run();
};

#endif // !GAME_H
