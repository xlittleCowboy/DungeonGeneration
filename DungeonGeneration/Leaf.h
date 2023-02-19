#pragma once

#include <SFML/Graphics.hpp>

class Leaf
{
private:
	Leaf* FirstLeaf;
	Leaf* SecondLeaf;

	Leaf* RoomLeaf;
	Leaf* CorridorLeaf;

	int Level = 0;

	sf::RectangleShape LeafShape;
	
public:
	Leaf(sf::Vector2f Position, sf::Vector2f Size,
		sf::Color FillColor = sf::Color::Transparent, sf::Color OutlineColor = sf::Color::White,
		float OutlineThickness = 5.0f);

	Leaf* GetFirstLeaf() { return FirstLeaf; }
	Leaf* GetSecondLeaf() { return SecondLeaf; }

	void SetFirstLeaf(Leaf* Leaf);
	void SetSecondLeaf(Leaf* Leaf);

	Leaf* GetRoomLeaf() { return RoomLeaf; }
	void SetRoomLeaf(Leaf* Leaf);

	Leaf* GetCorridorLeaf() { return CorridorLeaf; }
	void SetCorridorLeaf(Leaf* Leaf);

	int GetLevel() { return Level; }
	void IncreaseLevel(int Value = 1);

	sf::RectangleShape& GetLeafShape() { return LeafShape; }
};

