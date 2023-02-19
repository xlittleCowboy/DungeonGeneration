#include "Leaf.h"

Leaf::Leaf(sf::Vector2f Position, sf::Vector2f Size,
	sf::Color FillColor, sf::Color OutlineColor, float OutlineThickness)
{
	LeafShape.setPosition(Position);
	LeafShape.setSize(Size);
	LeafShape.setFillColor(FillColor);
	LeafShape.setOutlineColor(OutlineColor);
	LeafShape.setOutlineThickness(OutlineThickness);

	FirstLeaf = nullptr;
	SecondLeaf = nullptr;

	RoomLeaf = nullptr;
	CorridorLeaf = nullptr;
}

void Leaf::SetFirstLeaf(Leaf* Leaf)
{
	if (!Leaf) return;

	FirstLeaf = Leaf;
}

void Leaf::SetSecondLeaf(Leaf* Leaf)
{
	if (!Leaf) return;

	SecondLeaf = Leaf;
}

void Leaf::SetRoomLeaf(Leaf* Leaf)
{
	if (!Leaf) return;

	RoomLeaf = Leaf;
}

void Leaf::SetCorridorLeaf(Leaf* Leaf)
{
	if (!Leaf) return;

	CorridorLeaf = Leaf;
}

void Leaf::IncreaseLevel(int Value)
{
	if (Value <= 0) return;

	Level += Value;
}
