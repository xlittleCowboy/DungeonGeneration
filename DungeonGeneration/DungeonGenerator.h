#pragma once

#include <iostream>

#include "Leaf.h"
#include "Randomizer.h"

struct Vertex
{
	sf::Vector2f Location;

	Vertex* First;
	Vertex* Second;
};

class DungeonGenerator
{
private:
	Randomizer Rnd;

	std::vector<Leaf*> Rooms;
	std::vector<Leaf*> Corridors;

	std::vector<Vertex*> Verteces;

	float LineWidth = 3.0f;

	float MinLeafSize = 0.4f;
	float MaxLeafSize = 0.6f;

	float MinRoomPos = 0.1f;
	float MaxRoomPos = 0.2f;

	float MinRoomSize = 0.5f;
	float MaxRoomSize = 0.8f;

	float MinCorridorWidth = 5.0f;
	float MaxCorridorWidth = 5.0f;

	float DivideRatio = 1.0f;

public:
	~DungeonGenerator();

	Leaf* MainRoot;

	void GenerateDungeon(const int IterationsCount, const int Width, const int Height);

	void GenerateLeafs(const int IterationsCount, const int Width, const int Height, Leaf* Root);
	void GenerateRooms(Leaf* Root);

	void GenerateCorridors(Leaf* Root);

	void GenerateVerticalLeafs(const int IterationsCount, const int Width, const int Height, Leaf* LastLeaf);
	void GenerateHorizontalLeafs(const int IterationsCount, const int Width, const int Height, Leaf* LastLeaf);

	void DrawLeafs(sf::RenderWindow& Window, Leaf* Root);
	void DrawRooms(sf::RenderWindow& Window);
	void DrawCorridors(sf::RenderWindow& Window);
	void DrawPoints(sf::RenderWindow& Window);

	Vertex* FindNearestVertex(Vertex* Main, Vertex* Except);
	void FindNearestVertices();
	void AddVertex(sf::Vector2f Location);
};