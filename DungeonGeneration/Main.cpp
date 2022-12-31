#include <SFML/Graphics.hpp>

#include "DungeonGenerator.h"

int main()
{
    sf::RenderWindow Window(sf::VideoMode(800, 800), "Dungeon Generator");

    int IterationsCount = 3;

    DungeonGenerator Generator;
    Generator.GenerateDungeon(IterationsCount, 700, 700);

    while (Window.isOpen())
    {
        sf::Event event;
        while (Window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                Window.close();
        }

        Window.clear();

        Generator.DrawLeafs(Window, Generator.MainRoot);
        Generator.DrawPoints(Window);
        //Generator.DrawCorridors(Window);
        //Generator.DrawRooms(Window);

        Window.display();
    }

    return 0;
}