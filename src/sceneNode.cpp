#include "..\include\sceneNode.h"

#include <algorithm>
#include <assert.h>

SceneNode::SceneNode() {
	m_parent = nullptr;
}

void SceneNode::attachChild(Ptr child) {
	child->m_parent = this;
	m_children.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode & node) {
	auto found = std::find_if (m_children.begin(), m_children.end(),
		[&](Ptr& p) -> bool {return p.get() == &node; });

	assert(found != m_children.end());

	Ptr result = std::move(*found);
	result->m_parent = nullptr;
	m_children.erase(found);
	return result;
}

void SceneNode::update(sf::Time dt) {
	updateCurrent(dt);
	updateChildre(dt);
}

void SceneNode::draw(sf::RenderTarget & target, sf::RenderStates states) const {
	states.transform *= getTransform(); //Combine les transforms de tout les parents

	drawCurrent(target, states);

	for (const Ptr& child : m_children) {
		child->draw(target, states);
	}
}

void SceneNode::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const {
}

void SceneNode::onCommand(const Command & command, sf::Time dt) {
	if (command.category & getCategory()) {
		command.action(*this, dt);
	}

	for (Ptr& child : m_children) {
		child->onCommand(command, dt);
	}
}

unsigned int SceneNode::getCategory() const {
	return Category::SCENE;
}

sf::Transform SceneNode::getWorldTransform() const {
	sf::Transform transform = sf::Transform::Identity;

	for (const SceneNode* node = this; node != nullptr; node = node->m_parent) {
		transform = node->getTransform() * transform;
	}

	return transform;
}

sf::Vector2f SceneNode::getWorldPosition() const {
	return getWorldTransform() * sf::Vector2f();
}

void SceneNode::updateCurrent(sf::Time) {
}

void SceneNode::updateChildre(sf::Time dt) {
	for (const Ptr& child: m_children) {
		child->update(dt);
	}
}

void CommandQueue::push(const Command & command) {
	m_queue.push(command);
}

Command CommandQueue::pop() {
	Command command = m_queue.front();
	m_queue.pop();
	return command;
}

bool CommandQueue::isEmpty() {
	return m_queue.empty();
}

Command::Command() {
	category = Category::NONE;
}

