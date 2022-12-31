#pragma once

#include <SFML/Graphics.hpp>

class Leaf
{
private:
	sf::Vector2f Position;
	sf::Vector2f Size;
	
public:
	Leaf(sf::Vector2f Position, sf::Vector2f Size);

	Leaf* First;
	Leaf* Second;

	int Level = 0;

	sf::Color Color;

	std::vector<Leaf*> ConnectedRooms;

	sf::Vector2f GetPosition();
	sf::Vector2f GetSize();
};

