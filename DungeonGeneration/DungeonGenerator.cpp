#include "DungeonGenerator.h"

DungeonGenerator::~DungeonGenerator()
{
	ClearDungeon(MainRoot);
}

void DungeonGenerator::MoveOnNextLevel(Leaf* Root, int IterationsCount, int Width, int Height)
{
	Root->GetFirstLeaf()->IncreaseLevel(Root->GetLevel() + 1);
	Root->GetSecondLeaf()->IncreaseLevel(Root->GetLevel() + 1);

	GenerateLeafs(IterationsCount, Width, Height, Root->GetFirstLeaf());
	GenerateLeafs(IterationsCount, Width, Height, Root->GetSecondLeaf());
}

void DungeonGenerator::GenerateDungeon(int IterationsCount, int Width, int Height,
	sf::Color CorridorColor, bool RandomizeRoomColor, sf::Color RoomColor)
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

	GenerateRooms(MainRoot, RandomizeRoomColor, RoomColor);
	GenerateCorridors(MainRoot, CorridorColor);
}

void DungeonGenerator::GenerateRooms(Leaf* Root, bool RandomizeRoomColor, sf::Color RoomColor)
{
	if (!Root->GetFirstLeaf() || !Root->GetSecondLeaf())
	{
		sf::RectangleShape LeafShape = Root->GetLeafShape();

		int X = Rnd.GetRandomNumber(LeafShape.getPosition().x + LeafShape.getSize().x * MinRoomPos,
			LeafShape.getPosition().x + LeafShape.getSize().x * MaxRoomPos);

		int Y = Rnd.GetRandomNumber(LeafShape.getPosition().y + LeafShape.getSize().y * MinRoomPos,
			LeafShape.getPosition().y + LeafShape.getSize().y * MaxRoomPos);

		int SizeX = Rnd.GetRandomNumber((LeafShape.getSize().x - (X - LeafShape.getPosition().x)) * MinRoomSize,
			(LeafShape.getSize().x -  (X - LeafShape.getPosition().x)) * MaxRoomSize);

		int SizeY = Rnd.GetRandomNumber((LeafShape.getSize().y - (Y - LeafShape.getPosition().y)) * MinRoomSize,
			(LeafShape.getSize().y - (Y - LeafShape.getPosition().y)) * MaxRoomSize);

		if (RandomizeRoomColor)
		{
			RoomColor = sf::Color(Rnd.GetRandomNumber(0, 255), Rnd.GetRandomNumber(0, 255), Rnd.GetRandomNumber(0, 255));
		}

		Leaf* RoomLeaf = new Leaf(sf::Vector2f(X, Y), sf::Vector2f(SizeX, SizeY), RoomColor);

		Root->SetRoomLeaf(RoomLeaf);
	}
	else
	{
		GenerateRooms(Root->GetFirstLeaf(), RandomizeRoomColor, RoomColor);
		GenerateRooms(Root->GetSecondLeaf(), RandomizeRoomColor, RoomColor);
	}
}

void DungeonGenerator::GenerateCorridors(Leaf* Root, sf::Color CorridorColor)
{
	if (Root->GetFirstLeaf() && Root->GetSecondLeaf())
	{
		sf::RectangleShape FirstLeafShape = Root->GetFirstLeaf()->GetLeafShape();
		sf::RectangleShape SecondLeafShape = Root->GetSecondLeaf()->GetLeafShape();

		int X1 = (FirstLeafShape.getPosition().x + FirstLeafShape.getSize().x / 2);
		int Y1 = (FirstLeafShape.getPosition().y + FirstLeafShape.getSize().y / 2);

		int X2 = (SecondLeafShape.getPosition().x + SecondLeafShape.getSize().x / 2);
		int Y2 = (SecondLeafShape.getPosition().y + SecondLeafShape.getSize().y / 2);

		int SizeX = X2 - X1;
		int SizeY = Y2 - Y1;

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

		Leaf* Corridor = new Leaf(sf::Vector2f(X1, Y1), sf::Vector2f(SizeX, SizeY), CorridorColor);

		Root->SetCorridorLeaf(Corridor);

		GenerateCorridors(Root->GetFirstLeaf(), CorridorColor);
		GenerateCorridors(Root->GetSecondLeaf(), CorridorColor);
	}
}

void DungeonGenerator::GenerateLeafs(int IterationsCount, int Width, int Height, Leaf* Root)
{
	if (!Root || Root->GetLevel() >= IterationsCount)
	{
		return;
	}

	sf::RectangleShape LeafShape = Root->GetLeafShape();

	if (LeafShape.getSize().x / LeafShape.getSize().y < DivideRatio)
	{
		GenerateHorizontalLeafs(IterationsCount, Width, Height, Root);
	}
	else if (LeafShape.getSize().y / LeafShape.getSize().x < DivideRatio)
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

void DungeonGenerator::GenerateVerticalLeafs(int IterationsCount, int Width, int Height, Leaf* Root)
{
	sf::RectangleShape RootLeafShape = Root->GetLeafShape();

	Leaf* FirstLeaf = new Leaf(RootLeafShape.getPosition(),
		sf::Vector2f(Rnd.GetRandomNumber(RootLeafShape.getSize().x * MinLeafSize,
			RootLeafShape.getSize().x * MaxLeafSize), RootLeafShape.getSize().y));

	Root->SetFirstLeaf(FirstLeaf);

	sf::RectangleShape FirstLeafShape = FirstLeaf->GetLeafShape();

	Leaf* SecondLeaf = new Leaf(sf::Vector2f(FirstLeafShape.getPosition().x + FirstLeafShape.getSize().x,
		FirstLeafShape.getPosition().y),
		sf::Vector2f(RootLeafShape.getSize().x - FirstLeafShape.getSize().x, RootLeafShape.getSize().y));

	Root->SetSecondLeaf(SecondLeaf);

	MoveOnNextLevel(Root, IterationsCount, Width, Height);
}

void DungeonGenerator::GenerateHorizontalLeafs(int IterationsCount, int Width, int Height, Leaf* Root)
{
	sf::RectangleShape RootLeafShape = Root->GetLeafShape();

	Leaf* FirstLeaf = new Leaf(RootLeafShape.getPosition(), sf::Vector2f(RootLeafShape.getSize().x,
		Rnd.GetRandomNumber(RootLeafShape.getSize().y * MinLeafSize, RootLeafShape.getSize().y * MaxLeafSize)));

	Root->SetFirstLeaf(FirstLeaf);

	sf::RectangleShape FirstLeafShape = FirstLeaf->GetLeafShape();

	Root->SetSecondLeaf(new Leaf(sf::Vector2f(FirstLeafShape.getPosition().x,
		FirstLeafShape.getPosition().y + FirstLeafShape.getSize().y),
		sf::Vector2f(RootLeafShape.getSize().x, RootLeafShape.getSize().y - FirstLeafShape.getSize().y)));

	MoveOnNextLevel(Root, IterationsCount, Width, Height);
}

void DungeonGenerator::DrawLeafs(sf::RenderWindow& Window, Leaf* Root)
{
	if (!Root) return;

	Window.draw(Root->GetLeafShape());

	DrawLeafs(Window, Root->GetFirstLeaf());
	DrawLeafs(Window, Root->GetSecondLeaf());
}

void DungeonGenerator::DrawRooms(sf::RenderWindow& Window, Leaf* Root)
{
	if (!Root) return;

	Leaf* RoomLeaf = Root->GetRoomLeaf();

	if (RoomLeaf)
	{
		Window.draw(RoomLeaf->GetLeafShape());
	}

	DrawRooms(Window, Root->GetFirstLeaf());
	DrawRooms(Window, Root->GetSecondLeaf());
}

void DungeonGenerator::DrawCorridors(sf::RenderWindow& Window, Leaf* Root)
{
	if (!Root) return;

	Leaf* CorridorLeaf = Root->GetCorridorLeaf();

	if (CorridorLeaf)
	{
		Window.draw(CorridorLeaf->GetLeafShape());
	}

	DrawCorridors(Window, Root->GetFirstLeaf());
	DrawCorridors(Window, Root->GetSecondLeaf());
}

void DungeonGenerator::ClearDungeon(Leaf* Root)
{
	if (!Root) return;

	ClearDungeon(Root->GetFirstLeaf());
	ClearDungeon(Root->GetSecondLeaf());
	ClearDungeon(Root->GetRoomLeaf());
	ClearDungeon(Root->GetCorridorLeaf());

	delete Root;
}

void DungeonGenerator::RebuildDungeon(int IterationsCount, int Width, int Height,
	sf::Color CorridorColor, bool RandomizeRoomColor, sf::Color RoomColor)
{
	ClearDungeon(MainRoot);
	GenerateDungeon(IterationsCount, Width, Height, CorridorColor, RandomizeRoomColor, RoomColor);
}

Leaf* DungeonGenerator::GetMainRoot()
{
	return MainRoot;
}
