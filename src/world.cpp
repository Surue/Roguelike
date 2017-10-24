#include "..\include\world.h"

#include "SpriteNode.h"
#include "monster.h"

#include <iostream>

World::World(sf::RenderWindow & window) 
	: m_window(window)
	, m_worldView(window.getDefaultView())
	, m_spawnPosition (sf::Vector2f(100, 100))
	, m_worldBounds(0.f, 0.f, m_worldView.getSize().x, m_worldView.getSize().y) {
	loadTextures();
	buildScene();

	m_worldView.setCenter(m_spawnPosition);
}

void World::update(sf::Time dt) {
	m_worldView.setCenter(m_player->getPosition());
	m_player->setVelocity(0.f, 0.f);

	while (!m_commandQueue.isEmpty()) {
		m_sceneGraph.onCommand(m_commandQueue.pop(), dt);
	}

	sf::Vector2f velocity(m_player->getVelocity());

	if (velocity.x != 0.f && velocity.y != 0.f) {
		m_player->setVelocity(velocity / std::sqrt(2.f));
	}

	m_sceneGraph.update(dt);
}

void World::draw() {
	m_window.setView(m_worldView);
	m_window.draw(m_sceneGraph);
}

CommandQueue & World::getCommandQueue(){
	return m_commandQueue;
}

void World::loadTextures() {
	m_textures.load(Textures::Warrior, "data/textures/Warrior.png");
	m_textures.load(Textures::Archer, "data/textures/Archer.png");
	m_textures.load(Textures::Bones, "data/textures/Bones.png");
	m_textures.load(Textures::Cobble, "data/textures/Cobble.png");
}

void World::buildScene() {
	for (std::size_t i = 0; i < LENGTH; ++i) {
		SceneNode::Ptr layer(new SceneNode());
		m_sceneLayers[i] = layer.get();

		m_sceneGraph.attachChild(std::move(layer));
	}

	//Creation Background
	sf::Texture& texture = m_textures.get(Textures::Cobble);
	sf::IntRect textureRect(m_worldBounds);
	texture.setRepeated(true);

	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(m_worldBounds.left, m_worldBounds.top);

	m_sceneLayers[BACKGROUND]->attachChild(std::move(backgroundSprite));

	//Creation player
	std::unique_ptr<Hero> hero(new Hero(Hero::Warrior, m_textures));
	m_player = hero.get();
	m_player->setPosition(m_spawnPosition);
	m_player->setVelocity(0.f, 0.f);
	m_sceneLayers[ENTITY]->attachChild(std::move(hero));

	//m_player->setVelocity(100.f, 0.f);

	std::unique_ptr<Monster> monster(new Monster(Monster::Archer, m_textures));
	Monster* m_monster = monster.get();
	m_monster->setPosition(m_spawnPosition + sf::Vector2f(100.f,100.f));
	m_sceneLayers[ENTITY]->attachChild(std::move(monster));
}
