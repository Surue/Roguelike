#include "..\include\world.h"

#include "SpriteNode.h"
#include "monster.h"
#include "room.h"

#include <iostream>

World::World(sf::RenderWindow & window) 
	: m_window(window)
	, m_worldView(window.getDefaultView())
	, m_spawnPosition (sf::Vector2f(0, 0))
	, m_worldBounds(0.f, 0.f, m_worldView.getSize().x, m_worldView.getSize().y) {
	loadTextures();
	buildScene();

	m_worldView.setCenter(m_spawnPosition);
}

void World::update(sf::Time dt) {
	m_worldView.setCenter(m_player->getPosition());
	m_player->setLinearVelocity(b2Vec2(0,0));

	while (!m_commandQueue.isEmpty()) {
		m_sceneGraph.onCommand(m_commandQueue.pop(), dt);
	}

	b2Vec2 velocity(m_player->getLinearVelocity());

	if (velocity.x != 0.f && velocity.y != 0.f) {
		m_player->setLinearVelocity(velocity);
	}

	m_sceneGraph.update(dt);
}

void World::draw() {
	m_window.setView(m_worldView);
	m_window.draw(m_sceneGraph);
}

void World::step(float timeStep, int velocityIteration, int positionIteration) {
	m_physicalWorld.Step(timeStep, velocityIteration, positionIteration);
}

CommandQueue & World::getCommandQueue(){
	return m_commandQueue;
}

void World::loadTextures() {
	m_textures.load(Textures::Warrior, "data/textures/Warrior.png");
	m_textures.load(Textures::Archer, "data/textures/Archer.png");
	m_textures.load(Textures::Bones, "data/textures/Bones.png");
	m_textures.load(Textures::Cobble, "data/textures/Cobble.png");
	m_textures.load(Textures::Wall, "data/textures/Wall.png");
	m_textures.load(Textures::Ground, "data/textures/Ground.png");
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

	//Creation Room 0
	std::unique_ptr<Room> room(new Room());
	std::vector<std::vector<int>> arr;
	for (int i =0; i < 4; i++) {
		std::vector<int> tmp;
		for (int j = 0; j < 4; j++) {
			if (i == 1 && j == 1) {
				tmp.push_back(0);
			}else {
				tmp.push_back(1);
			}
		}
		arr.push_back(tmp);
	}
	room->build(m_physicalWorld, arr, m_textures);
	m_sceneLayers[TILE]->attachChild(std::move(room));

	//Creation player
	std::unique_ptr<Hero> hero(new Hero(m_physicalWorld, Hero::Warrior, m_textures, m_spawnPosition));
	m_player = hero.get();
	m_sceneLayers[ENTITY]->attachChild(std::move(hero));

	std::unique_ptr<Monster> monster(new Monster(m_physicalWorld, Monster::Archer, m_textures, sf::Vector2f(100.f, 100.f)));
	Monster* m_monster = monster.get();
	m_sceneLayers[ENTITY]->attachChild(std::move(monster));
}
