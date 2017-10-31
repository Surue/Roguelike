#include "..\include\player.h"

#include "hero.h"
#include <iostream>

void Player::handleEvent(const sf::Event & event, CommandQueue & commands) {
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
		Command output;
		output.category = Category::HERO;
		output.action = [](SceneNode& node, sf::Time) {
			std::cout << node.getPosition().x << ", " << node.getPosition().y << "\n";
		};
		commands.push(output);
	}
}

void Player::handleRealtimeInput(CommandQueue & commands) {
	const float playerSpeed = 120.f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		Command moveLeft;
		moveLeft.category = Category::HERO;
		moveLeft.action = derivedAction<Hero>(HeroMover(-playerSpeed, 0.f));
		commands.push(moveLeft);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		Command moveRight;
		moveRight.category = Category::HERO;
		moveRight.action = derivedAction<Hero>(HeroMover(+playerSpeed, 0.f));
		commands.push(moveRight);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		Command moveUp;
		moveUp.category = Category::HERO;
		moveUp.action = derivedAction<Hero>(HeroMover(0.f, -playerSpeed));
		commands.push(moveUp);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		Command moveDown;
		moveDown.category = Category::HERO;
		moveDown.action = derivedAction<Hero>(HeroMover(0.f, +playerSpeed));
		commands.push(moveDown);
	}
}
