#include "Leaf.h"

Leaf::Leaf(sf::Vector2f Position, sf::Vector2f Size)
{
	this->Position = Position;
	this->Size = Size;
}

sf::Vector2f Leaf::GetPosition()
{
	return Position;
}

sf::Vector2f Leaf::GetSize()
{
	return Size;
}