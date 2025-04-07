#pragma once
#include "Snake.h"

class Game
{
public:
	Game();

	void run();

private:
	static const int m_width = 20;
	static const int m_height = 20;

	Snake snake;

	bool isRunning;

	void processInput();
	void update();
	void render();
	void clearScreen();
};