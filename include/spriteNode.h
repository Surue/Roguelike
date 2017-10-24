#ifndef SPRITE_NODE_H
#define SPRITE_NODE_H

#include "sceneNode.h"

class SpriteNode : public SceneNode {
public:
	explicit SpriteNode(const sf::Texture&);
	SpriteNode(const sf::Texture&, const sf::IntRect&);

private:
	virtual void drawCurrent(sf::RenderTarget&, sf::RenderStates) const;
private:
	sf::Sprite m_sprite;
};

#endif // !SPRITE_NODE_H
