#include "Game.h"

void Game::initializeVariables()
{
	window = nullptr;
}

void Game::initWindow()
{
	videoMode.height = WINDOWHEIGHT;
	videoMode.width = WINDOWWIDTH;

	window = new sf::RenderWindow(videoMode, "Game of life", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(144);
}

void Game::initGrids()
{
	numGridRows = WINDOWHEIGHT / GRIDSQUARESIZE;
	numGridColumns = WINDOWWIDTH / GRIDSQUARESIZE;
	grid = new bool*[numGridRows];
	tempGrid = new bool* [numGridRows];
	for (int i = 0; i < numGridRows; i++) 
	{
		grid[i] = new bool[numGridColumns];
		tempGrid[i] = new bool[numGridColumns];
	}
	for (int i = 0; i < numGridRows; i++)
	{
		for (int j = 0; j < numGridColumns; j++)
		{
			grid[i][j] = false;
		}
	}

	grid[40][40] = true;
	grid[40][41] = true;
	grid[40][42] = true;
	grid[41][41] = true;
	grid[41][42] = true;
	grid[41][43] = true;
}

void Game::destroyGrids()
{
	for (int i = 0; i < numGridRows; i++) 
	{
		delete grid[i];
		delete tempGrid[i];
	}
	delete grid;
	delete tempGrid;
}

void Game::initLiveSquare()
{
	const int outlineThickness = 1;
	liveSquare.setSize(sf::Vector2f(GRIDSQUARESIZE - outlineThickness, GRIDSQUARESIZE - outlineThickness));
	liveSquare.setFillColor(sf::Color::White);
	liveSquare.setOutlineColor(sf::Color::Black);
	liveSquare.setOutlineThickness(outlineThickness);
}

void Game::stepForwardGameOfLife()
{
	/*
	***RULES***
	1. if a cell is alive, then it stays alive if it has either 2 or 3 live neighbors
	2. if the cell is dead, then it springs to life only if it has 3 live neighbors
	*/
	auto checkCell = [&](int row, int col)
	{
		int liveNeighbors = 0;
		if (row + 1 < numGridRows) {
			if (grid[row + 1][col]) liveNeighbors++;
		}
		if (row - 1 >= 0) {
			if (grid[row - 1][col]) liveNeighbors++;
		}
		if (col + 1 < numGridColumns) {
			if (grid[row][col + 1]) liveNeighbors++;
		}
		if (col - 1 >= 0) {
			if (grid[row][col - 1]) liveNeighbors++;
		}
		if (row + 1 < numGridRows && col + 1 < numGridColumns) {
			if (grid[row + 1][col + 1]) liveNeighbors++;
		}
		if (row - 1 >= 0 && col + 1 < numGridColumns) {
			if (grid[row - 1][col + 1]) liveNeighbors++;
		}
		if (row + 1 < numGridRows && col - 1 >= 0) {
			if (grid[row + 1][col - 1]) liveNeighbors++;
		}
		if (row - 1 >= 0 && col - 1 >= 0) {
			if (grid[row - 1][col - 1]) liveNeighbors++;
		}
		if (liveNeighbors == 3) return true;
		if (liveNeighbors == 2 && grid[row][col]) return true;
		return false;
	};
	for (int i = 0; i < numGridRows; i++)
	{
		for (int j = 0; j < numGridColumns; j++)
		{
			tempGrid[i][j] = checkCell(i, j);
		}
	}
	for (int i = 0; i < numGridRows; i++)
	{
		for (int j = 0; j < numGridColumns; j++)
		{
			grid[i][j] = tempGrid[i][j];
		}
	}
}
Game::Game()
{
	initializeVariables();
	initWindow();
	initGrids();
	initLiveSquare();
}

Game::~Game()
{
	delete window;
	destroyGrids();
}

void Game::pollEvents()
{
	while (window->pollEvent(gameEvent))
	{
		switch (gameEvent.type)
		{
		case sf::Event::Closed:
			window->close();
			break;
		case sf::Event::KeyPressed:
			if (gameEvent.key.code == sf::Keyboard::Escape) window->close();
			if (gameEvent.key.code == sf::Keyboard::F) stepForwardGameOfLife();
			break;
		}
	}
}

void Game::update()
{
	pollEvents();
}

void Game::render()
{
	window->clear(sf::Color(255,0,0,255)); // Clears the old frame

	// Draw everything here
	for (int i = 0; i < numGridRows; i++)
	{
		for (int j = 0; j < numGridColumns; j++)
		{
			if ( grid[i][j] )
			{
				liveSquare.setPosition(sf::Vector2f(j * GRIDSQUARESIZE, i * GRIDSQUARESIZE));
				window->draw(liveSquare);
			}
		}
	}

	window->display(); // Renders new frame
}

bool Game::running()
{
	return window->isOpen();
}
