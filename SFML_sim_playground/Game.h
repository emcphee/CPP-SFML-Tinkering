#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "constants.h"

class Game
{
private:
	
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event gameEvent;

	sf::RectangleShape liveSquare;

	void initializeVariables();
	void initWindow();

	void initGrids();
	void destroyGrids();
	int numGridRows;
	int numGridColumns;
	bool** grid;
	bool** tempGrid;

	void initLiveSquare();
	void stepForwardGameOfLife();

public:
	Game();
	virtual ~Game();

	void pollEvents();
	void update();
	void render();

	// returns true until the game is closed.
	bool running();
};