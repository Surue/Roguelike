#ifndef PLAYER_H
#define PLAYER_H

#include "hero.h"

class Player {
private:
	struct HeroMover {
		HeroMover(float x, float y) : velocity(x, y) {
		}

		void operator() (Hero& hero, sf::Time) const {
			hero.setVelocity(velocity);
		}

		sf::Vector2f velocity;
	};
public:
	void handleEvent(const sf::Event&, CommandQueue&);
	void handleRealtimeInput(CommandQueue&);
};

#endif // !PLAYER_H
