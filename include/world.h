#ifndef WORLD_H
#define WORLD_H

#include <array>

#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>

#include "textureManager.h"
#include "sceneNode.h"
#include "hero.h"

class World {
public:
	explicit World(sf::RenderWindow& window);
	void update(sf::Time);
	void draw();

	void step(float, int, int);

	CommandQueue& getCommandQueue();
private:
	void loadTextures();
	void buildScene();
private:
	enum Layer {
		BACKGROUND,
		TILE,
		ENTITY,
		PARTICLE,
		LENGTH
	};
	CommandQueue m_commandQueue;
	sf::RenderWindow& m_window;
	sf::View m_worldView;
	TextureManager m_textures;
	SceneNode m_sceneGraph;
	std::array<SceneNode*, LENGTH> m_sceneLayers;
	sf::FloatRect m_worldBounds;
	sf::Vector2f m_spawnPosition;
	Hero* m_player;
	b2World m_physicalWorld = b2World(b2Vec2(0, 0));
};

#endif // !WORLD_H
