#include <iostream>
#include "Game.h"
#include <conio.h>
#include <thread>
#include <chrono>



Game::Game() : snake(m_width / 2, m_height / 2), isRunning(true) {}


void Game::run()
{
	while (isRunning)
	{
		clearScreen();
		processInput();
		update();
		render();
		std::this_thread::sleep_for(std::chrono::milliseconds(150));
	}

}

void Game::processInput()
{
	if (_kbhit())
	{
		int key = _getche();

		if (key == 224)
		{
			int arrow = _getch();
			switch (arrow)
			{
				case 72: snake.ChangeDirection(Direction::UP);
				break;
				case 80: snake.ChangeDirection(Direction::DOWN);
				break;
				case 75: snake.ChangeDirection(Direction::LEFT);
				break;
				case 77: snake.ChangeDirection(Direction::RIGHT);
				break;
			}
		}
		if (key == 27)
		{
			isRunning = false;
		}

	}
}

void Game::update()
{
	snake.move();
	Position head = snake.getHeadPosition();

	if (head.x < 0 || head.x >= m_width || head.y < 0 || head.x >= m_height)
	{
		isRunning = false;
	}
}

void Game::render()
{
	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			bool printed = false;

			for (const Position& segment : snake.getBody())
			{
				if (segment.x == x && segment.y == y)
				{
					std::cout << "0";
					printed = true;
					break;
				}
			}

			if (!printed)
			{
				if (y == 0 || y == m_height - 1 || x == 0 || x == m_width - 1)
				{
					std::cout << "#";
				}
				else 
				{
					std::cout << " ";
				}
			}
		}
		std::cout << "\n";
	}
}

void Game::clearScreen()
{
	system("cls");
}