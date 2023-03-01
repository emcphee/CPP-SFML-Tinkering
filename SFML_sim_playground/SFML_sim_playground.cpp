#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Game.h"

int main()
{
    Game* game = new Game();

    // Frame loop
    while (game->running())
    {
        game->update();
        game->render();
    }
    return 0;
}
