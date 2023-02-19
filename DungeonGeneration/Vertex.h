#pragma once

#include <SFML/Graphics.hpp>

class HalfEdge;

class Vertex
{
public:
	Vertex();
	Vertex(const sf::Vector2f& Location);

	sf::Vector2f Location;

	Vertex* First;
	Vertex* Second;
};

