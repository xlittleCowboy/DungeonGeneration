#include "Vertex.h"

Vertex::Vertex()
{
	Location = sf::Vector2f();
}

Vertex::Vertex(const sf::Vector2f& Location)
{
	this->Location = Location;
}