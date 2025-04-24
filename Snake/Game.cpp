#include <iostream>
#include "Game.h"
#include <conio.h>
#include <thread>
#include <chrono>



Game::Game() : snake(m_width / 2, m_height / 2), isRunning(true), m_score(0)
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	generateFood();
}


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

	clearScreen();
	std::cout << "Game Over" << std::endl;
	std::cout << "Your Score:" << m_score << std::endl;
	std::cout << "Press any key to exit";
	_getch();

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
	Position head = snake.getHeadPosition();
	Position next = head;

	switch (snake.getDirection())
	{
		case Direction::UP: next.y--;
		break;
		case Direction::DOWN: next.y++;
		break;
		case Direction::LEFT: next.x--;
		break;
		case Direction::RIGHT: next.x++;
		break;
	}

	bool grow = (next.x == food.x && next.y == food.y);

	snake.move(grow ? true : false);

	if (grow)
	{
		m_score++;
		generateFood();
	}

	Position newHead = snake.getHeadPosition();
	if (newHead.x < 0 || newHead.x >= m_width || newHead.y < 0 || newHead.x >= m_height)
	{
		isRunning = false;
		return;
	}

	const std::vector<Position>& body = snake.getBody();
	for (size_t i = 1; i < body.size(); i++)
	{
		if (body[i].x == newHead.x && body[i].y == newHead.y)
		{
			isRunning = false;
			return;
		}
	}
}

void Game::render()
{

	std::cout << "Score:" << m_score << '\n';

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

			if (!printed && x == food.x && y == food.y)
			{
				std::cout << "*";
				printed = true;
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

	std::cout << "Use arrow keys to move. Press ESC to quit." << '\n';
}

void Game::clearScreen()
{
	system("cls");
}


void Game::generateFood()
{
	while (true)
	{
		int x = rand() % (m_width - 2) + 1;
		int y = rand() % (m_height - 2) + 1;

		bool onSnake = false;
		for (const Position& segment : snake.getBody())
		{
			if (segment.x == x && segment.y == y)
			{
				onSnake = true;
				break;
			}
		}

		if (!onSnake)
		{
			food = { x, y };
			return;
		}

	}
}