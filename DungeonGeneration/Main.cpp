#include <SFML/Graphics.hpp>
#include "DungeonGenerator.h"

/*
    CHANGE DUNGEON PARAMETERS AT THE BEGINING OF main()
    PRESS R TO REBUILD THE DUNGEON
*/

int main()
{
    // Window Settings
    int WindowWidth = 800;
    int WindowHeight = 800;

    sf::RenderWindow Window(sf::VideoMode(WindowWidth, WindowHeight), "Dungeon Generator");

    // Dungeon Settings
    int IterationsCount = 4;
    int DungeonWidth = 700;
    int DungeonHeight = 700;
    sf::Color CorridorColor = sf::Color(233, 0, 100);
    bool RandomizeRoomColor = false;
    sf::Color RoomColor = sf::Color(179, 0, 94);

    DungeonGenerator* Generator = new DungeonGenerator();
    Generator->GenerateDungeon(IterationsCount, DungeonWidth, DungeonHeight,
        CorridorColor, RandomizeRoomColor, RoomColor);

    /* Main Loop */
    while (Window.isOpen())
    {
        sf::Event Event;
        while (Window.pollEvent(Event))
        {
            if (Event.type == sf::Event::Closed)
                Window.close();

            if (Event.type == sf::Event::KeyPressed)
            {
                if (Event.key.code == sf::Keyboard::R) // Dungeon Rebuild Bind
                {
                    if (Generator)
                    {
                        Generator->RebuildDungeon(IterationsCount, DungeonWidth, DungeonHeight,
                            CorridorColor, RandomizeRoomColor, RoomColor);
                    }
                }
            }
        }

        /* Draw & Display */
        Window.clear();

        // Draw Background
        sf::RectangleShape Background;
        Background.setSize(sf::Vector2f(WindowWidth, WindowHeight));
        Background.setFillColor(sf::Color(6, 0, 71));
        Window.draw(Background);

        // Draw Rooms & Corridors
        Generator->DrawCorridors(Window, Generator->GetMainRoot());
        Generator->DrawRooms(Window, Generator->GetMainRoot());

        Window.display();
    }

    delete Generator;

    return 0;
}