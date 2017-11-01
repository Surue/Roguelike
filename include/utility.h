#ifndef UTILITY_H
#define UTILITY_H

#include <Box2D\Box2D.h>
#include <SFML\System.hpp>

float pixel2meter(float pixel);
float meter2pixel(float meter);

b2Vec2 pixel2meter(sf::Vector2f pixels);
sf::Vector2f meter2pixel(b2Vec2 meters);

#endif // !UTILITY_H
