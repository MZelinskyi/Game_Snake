#pragma once
#include "Snake.h"
#include <string>
#include <fstream>

class Game
{
public:
	Game();

	void run();

private:
	static const int m_width = 30;
	static const int m_height = 15;
	int m_score = 0;
	int m_highScore = 0;

	Snake snake;
	Position food;

	bool isRunning;

	void processInput();
	void update();
	void render();
	void clearScreen();
	void showMenu();
	void loadingHighScore();
	void saveHighScore();

	void generateFood();
};