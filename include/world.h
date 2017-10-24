#ifndef WORLD_H
#define WORLD_H

#include <array>

#include <SFML\Graphics.hpp>
#include "textureManager.h"
#include "sceneNode.h"
#include "hero.h"

class World {
public:
	explicit World(sf::RenderWindow& window);
	void update(sf::Time);
	void draw();

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
};

#endif // !WORLD_H
