#include "..\include\game.h"

void Game::processEvent() {
	CommandQueue& command = m_world.getCommandQueue();
	sf::Event event;
	while (m_window.pollEvent(event)) {
		switch (event.type)
		{
		case sf::Event::Closed:
			m_window.close();
			break;

		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape) {
				m_window.close();
			}
			break;
		}

		m_player.handleEvent(event, command);
	}

	m_player.handleRealtimeInput(command);
}

void Game::update(sf::Time dt) {
	m_world.update(dt);
}

void Game::render() {
	m_window.clear();
	m_world.draw();
	m_window.display();
}

Game::Game() : m_window(sf::VideoMode(640, 480), "Roguelike game"), m_world(m_window){
	isPaused = false;
}

Game::~Game() {
}

void Game::run() {
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (m_window.isOpen()) {
		m_world.step(timePerFrame.asSeconds(), 8, 3);

		processEvent();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame) {
			timeSinceLastUpdate -= timePerFrame;
			processEvent();
			if (!isPaused) {
				update(timePerFrame);
			}
		}
		
		render();
	}
}
