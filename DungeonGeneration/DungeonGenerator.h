#pragma once

#include <iostream>
#include "Leaf.h"
#include "Randomizer.h"
#include "MathHelper.h"

class DungeonGenerator
{
private:
	Leaf* MainRoot;

	Randomizer Rnd;

	float LineWidth = 3.0f;

	float MinLeafSize = 0.4f;
	float MaxLeafSize = 0.6f;

	float MinRoomPos = 0.1f;
	float MaxRoomPos = 0.2f;

	float MinRoomSize = 0.5f;
	float MaxRoomSize = 0.9f;

	float CorridorWidth = 5.0f;

	float DivideRatio = 1.0f;

	void GenerateLeafs(int IterationsCount, int Width, int Height, Leaf* Root);
	void GenerateRooms(Leaf* Root, bool RandomizeRoomColor, sf::Color RoomColor);
	void GenerateCorridors(Leaf* Root, sf::Color CorridorColor);
	void GenerateVerticalLeafs(int IterationsCount, int Width, int Height, Leaf* LastLeaf);
	void GenerateHorizontalLeafs(int IterationsCount, int Width, int Height, Leaf* LastLeaf);

	void MoveOnNextLevel(Leaf* Root, int IterationsCount, int Width, int Height);

	void ClearDungeon(Leaf* Root);

public:
	~DungeonGenerator();

	void GenerateDungeon(int IterationsCount, int Width, int Height,
		sf::Color CorridorColor = sf::Color::White, bool RandomizeRoomColor = true, sf::Color RoomColor = sf::Color::White);

	void DrawLeafs(sf::RenderWindow& Window, Leaf* Root);
	void DrawRooms(sf::RenderWindow& Window, Leaf* Root);
	void DrawCorridors(sf::RenderWindow& Window, Leaf* Root);

	void RebuildDungeon(int IterationsCount, int Width, int Height,
		sf::Color CorridorColor = sf::Color::White, bool RandomizeRoomColor = true, sf::Color RoomColor = sf::Color::White);

	Leaf* GetMainRoot();
};