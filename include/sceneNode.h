#ifndef SCENE_NODE_H
#define SCENE_NODE_H

#include <memory>
#include <vector>
#include <SFML\Graphics.hpp>
#include <assert.h>
#include <functional>
#include <queue>

class SceneNode;

struct Command {
	Command();

	std::function<void(SceneNode&, sf::Time)> action;
	unsigned int category;
};

class CommandQueue {
public:
	void push(const Command&);
	Command pop();
	bool isEmpty();
private:
	std::queue<Command> m_queue;
};

template <typename GameObject, typename Function> std::function<void(SceneNode&, sf::Time)> derivedAction(Function fn) {
	return [=](SceneNode& node, sf::Time dt) {
		assert(dynamic_cast<GameObject*>(&node) != nullptr);

		fn(static_cast<GameObject&>(node), dt);
	};
}

namespace Category {
	enum Type {
		NONE = 0,
		SCENE = 1 << 0,
		HERO = 1 << 1,
		MONSTER = 1 << 2
	};
}

class SceneNode :public sf::Transformable, public sf::Drawable, private sf::NonCopyable{
public:
	typedef std::unique_ptr<SceneNode> Ptr;
private:
	std::vector<Ptr> m_children;
	SceneNode* m_parent;

public:
	SceneNode();

	void attachChild(Ptr);
	Ptr detachChild(const SceneNode&);

	void update(sf::Time);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	void onCommand(const Command&, sf::Time);

	virtual unsigned int getCategory() const;
	sf::Transform getWorldTransform() const;
	sf::Vector2f getWorldPosition()const;

private:
	virtual void updateCurrent(sf::Time);
	void updateChildre(sf::Time);
};
#endif // ! SCENE_NODE_H


