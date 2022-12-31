#include "DungeonGenerator.h"


DungeonGenerator::~DungeonGenerator()
{
	for (size_t i = 0; i < Rooms.size(); i++)
	{
		delete Rooms[i];
	}

	for (size_t i = 0; i < Corridors.size(); i++)
	{
		delete Corridors[i];
	}
}

void DungeonGenerator::GenerateDungeon(const int IterationsCount, const int Width, const int Height)
{
	MainRoot = new Leaf(sf::Vector2f(50, 50), sf::Vector2f(Width, Height));
	if (Rnd.GetRandomNumber(0, 1) == 0) // Vertical Splitting
	{
		GenerateVerticalLeafs(IterationsCount, Width, Height, MainRoot);
	}
	else // Horizontal Splitting
	{
		GenerateHorizontalLeafs(IterationsCount, Width, Height, MainRoot);
	}

	GenerateRooms(MainRoot);
	GenerateCorridors(MainRoot);
	FindNearestVertices();
}

void DungeonGenerator::GenerateRooms(Leaf* Root)
{
	if (!Root->First || !Root->Second)
	{
		int X = Rnd.GetRandomNumber(Root->GetPosition().x + Root->GetSize().x * MinRoomPos,
			Root->GetPosition().x + Root->GetSize().x * MaxRoomPos);

		int Y = Rnd.GetRandomNumber(Root->GetPosition().y + Root->GetSize().y * MinRoomPos,
			Root->GetPosition().y + Root->GetSize().y * MaxRoomPos);

		int SizeX = Rnd.GetRandomNumber((Root->GetSize().x - (X - Root->GetPosition().x)) * MinRoomSize,
			(Root->GetSize().x -  (X - Root->GetPosition().x)) * MaxRoomSize);

		int SizeY = Rnd.GetRandomNumber((Root->GetSize().y - (Y - Root->GetPosition().y)) * MinRoomSize,
			(Root->GetSize().y - (Y - Root->GetPosition().y)) * MaxRoomSize);

		Leaf* Room = new Leaf(sf::Vector2f(X, Y), sf::Vector2f(SizeX, SizeY));
		//Room->Color = sf::Color(Rnd.GetRandomNumber(0, 255), Rnd.GetRandomNumber(0, 255), Rnd.GetRandomNumber(0, 255));
		Room->Color = sf::Color::White;

		Rooms.push_back(Room);
	}
	else
	{
		GenerateRooms(Root->First);
		GenerateRooms(Root->Second);
	}
}

void DungeonGenerator::GenerateCorridors(Leaf* Root)
{
	if (Root->First && Root->Second)
	{
		int X1 = (Root->First->GetPosition().x + Root->First->GetSize().x / 2);
		int Y1 = (Root->First->GetPosition().y + Root->First->GetSize().y / 2);

		int X2 = (Root->Second->GetPosition().x + Root->Second->GetSize().x / 2);
		int Y2 = (Root->Second->GetPosition().y + Root->Second->GetSize().y / 2);

		int SizeX = X2 - X1;
		int SizeY = Y2 - Y1;

		float CorridorWidth = Rnd.GetRandomNumber(MinCorridorWidth, MaxCorridorWidth);

		if (SizeX <= 0)
		{
			SizeX = CorridorWidth;
			X1 -= CorridorWidth / 2;
		}
		if (SizeY <= 0)
		{
			SizeY = CorridorWidth;
			Y1 -= CorridorWidth / 2;
		}

		Leaf* Corridor = new Leaf(sf::Vector2f(X1, Y1), sf::Vector2f(SizeX, SizeY));

		Corridors.push_back(Corridor);

		Root->First->ConnectedRooms.push_back(Root->Second);
		Root->Second->ConnectedRooms.push_back(Root->First);

		if (!Root->First->First)
		{
			AddVertex(sf::Vector2f(X1, Y1));
			AddVertex(sf::Vector2f(X2, Y2));
		}

		GenerateCorridors(Root->First);
		GenerateCorridors(Root->Second);
	}
}

void DungeonGenerator::GenerateLeafs(const int IterationsCount, const int Width, const int Height, Leaf* Root)
{
	if (!Root || Root->Level >= IterationsCount)
	{
		return;
	}

	if (Root->GetSize().x / Root->GetSize().y < DivideRatio)
	{
		GenerateHorizontalLeafs(IterationsCount, Width, Height, Root);
	}
	else if (Root->GetSize().y / Root->GetSize().x < DivideRatio)
	{
		GenerateVerticalLeafs(IterationsCount, Width, Height, Root);
	}
	else
	{
		if (Rnd.GetRandomNumber(0, 1) == 0) // Vertical Splitting
		{
			GenerateVerticalLeafs(IterationsCount, Width, Height, Root);
		}
		else // Horizontal Splitting
		{
			GenerateHorizontalLeafs(IterationsCount, Width, Height, Root);
		}
	}
}

void DungeonGenerator::GenerateVerticalLeafs(const int IterationsCount, const int Width, const int Height, Leaf* Root)
{
	Root->First = new Leaf(Root->GetPosition(),
		sf::Vector2f(Rnd.GetRandomNumber(Root->GetSize().x * MinLeafSize,
			Root->GetSize().x * MaxLeafSize),
			Root->GetSize().y));

	Root->Second = new Leaf(sf::Vector2f(Root->First->GetPosition().x + Root->First->GetSize().x,
		Root->First->GetPosition().y),
		sf::Vector2f(Root->GetSize().x - Root->First->GetSize().x, Root->GetSize().y));

	Root->First->Level = Root->Level + 1;
	Root->Second->Level = Root->Level + 1;

	GenerateLeafs(IterationsCount, Width, Height, Root->First);
	GenerateLeafs(IterationsCount, Width, Height, Root->Second);
}

void DungeonGenerator::GenerateHorizontalLeafs(const int IterationsCount, const int Width, const int Height, Leaf* Root)
{
	Root->First = new Leaf(Root->GetPosition(),
		sf::Vector2f(Root->GetSize().x, Rnd.GetRandomNumber(Root->GetSize().y * MinLeafSize,
			Root->GetSize().y * MaxLeafSize)));

	Root->Second = new Leaf(sf::Vector2f(Root->First->GetPosition().x,
		Root->First->GetPosition().y + Root->First->GetSize().y),
		sf::Vector2f(Root->GetSize().x, Root->GetSize().y - Root->First->GetSize().y));

	Root->First->Level = Root->Level + 1;
	Root->Second->Level = Root->Level + 1;

	GenerateLeafs(IterationsCount, Width, Height, Root->First);
	GenerateLeafs(IterationsCount, Width, Height, Root->Second);
}

void DungeonGenerator::DrawLeafs(sf::RenderWindow& Window, Leaf* Root)
{
	if (!Root) return;

	sf::RectangleShape Rectangle(sf::Vector2f(Root->GetSize().x, Root->GetSize().y));
	Rectangle.setPosition(Root->GetPosition().x, Root->GetPosition().y);
	Rectangle.setFillColor(sf::Color::Transparent);
	Rectangle.setOutlineThickness(LineWidth);
	Rectangle.setOutlineColor(sf::Color::White);

	Window.draw(Rectangle);

	DrawLeafs(Window, Root->First);
	DrawLeafs(Window, Root->Second);
}

void DungeonGenerator::DrawRooms(sf::RenderWindow& Window)
{
	for (size_t i = 0; i < Rooms.size(); i++)
	{
		sf::RectangleShape Rectangle(sf::Vector2f(Rooms[i]->GetSize().x, Rooms[i]->GetSize().y));
		Rectangle.setPosition(Rooms[i]->GetPosition().x, Rooms[i]->GetPosition().y);
		Rectangle.setFillColor(Rooms[i]->Color);

		Window.draw(Rectangle);
	}
}

void DungeonGenerator::DrawCorridors(sf::RenderWindow& Window)
{
	for (size_t i = 0; i < Corridors.size(); i++)
	{
		sf::RectangleShape Rectangle(sf::Vector2f(Corridors[i]->GetSize().x, Corridors[i]->GetSize().y));
		Rectangle.setPosition(Corridors[i]->GetPosition().x, Corridors[i]->GetPosition().y);
		Rectangle.setFillColor(sf::Color::White);

		Window.draw(Rectangle);
	}
}

void DungeonGenerator::DrawPoints(sf::RenderWindow& Window)
{
	for (auto i = Verteces.begin(); i < Verteces.end(); ++i)
	{
		sf::Vertex FirstLine[] =
		{
			sf::Vertex((*i)->Location),
			sf::Vertex((*i)->First->Location)
		};

		sf::Vertex SecondLine[] =
		{
			sf::Vertex((*i)->Location),
			sf::Vertex((*i)->Second->Location)
		};

		Window.draw(FirstLine, 2, sf::Lines);
		Window.draw(SecondLine, 2, sf::Lines);
	}
}

Vertex* DungeonGenerator::FindNearestVertex(Vertex* Main, Vertex* Except)
{
	Vertex* Nearest = nullptr;

	for (auto i = Verteces.begin(); i < Verteces.end(); ++i)
	{
		if (*i == Main) continue;

		if ((*i)->First == Main || (*i)->Second == Main) continue;

		if (!Nearest)
		{
			Nearest = *i;
			continue;
		}


		sf::Vector2f OldLengthVector = Nearest->Location - Main->Location;
		float OldLength = sqrt(OldLengthVector.x * OldLengthVector.x + OldLengthVector.y * OldLengthVector.y);

		sf::Vector2f NewLengthVector = (*i)->Location - Main->Location;
		float NewLength = sqrt(NewLengthVector.x * NewLengthVector.x + NewLengthVector.y * NewLengthVector.y);

		if (NewLength < OldLength) Nearest = *i;
	}

	return Nearest;
}

void DungeonGenerator::FindNearestVertices()
{
	for (auto i = Verteces.begin(); i < Verteces.end(); ++i)
	{
		Vertex* First = new Vertex();
		Vertex* Second = new Vertex();

		(*i)->First = FindNearestVertex(*i, nullptr);
		(*i)->Second = FindNearestVertex(*i, First);
	}
}

void DungeonGenerator::AddVertex(sf::Vector2f Location)
{
	Vertex* NewVertex = new Vertex();
	NewVertex->Location = Location;

	Verteces.push_back(NewVertex);
}
