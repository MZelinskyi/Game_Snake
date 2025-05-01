#include <iostream>
#include "Game.h"
#include <conio.h>
#include <thread>
#include <chrono>



Game::Game() : snake(m_width / 2, m_height / 2), isRunning(true), m_score(0), m_highScore(0)
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	loadingHighScore();
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

	saveHighScore();

	clearScreen();
	std::cout << "==== Game Over ====" << std::endl;
	std::cout << "Your Score:" << m_score << std::endl;
	std::cout << "High Score:" << m_highScore << std::endl;
	std::cout << "Press any key to return to menu...";
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
	if (newHead.x < 0 || newHead.x >= m_width - 1 || newHead.y <= 0 || newHead.y >= m_height - 1)
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

			const std::vector<Position>& body = snake.getBody();

			for (size_t i = 0; i < body.size(); i++)
			{
				if (body[i].x == x && body[i].y == y)
				{
					if (i == 0)
					{
						std::cout << "@";
					}
					else
					{
						std::cout << "&";
					}
					printed = true;
					break;
				}
			}

			if (!printed && x == food.x && y == food.y)
			{
				std::cout << "#";
				printed = true;
			}


			if (!printed)
			{
				if (y == 0 || y == m_height - 1 || x == 0 || x == m_width - 1)
				{
					std::cout << "*";
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


void Game::loadingHighScore()
{
	std::ifstream file("highscore.txt");
	if (file.is_open())
	{
		file >> m_highScore;
		file.close();
	}
	else
	{
		m_highScore = 0;
	}
}

void Game::saveHighScore()
{
	if (m_score > m_highScore)
	{
		std::ofstream file("highscore.txt");
		if (file.is_open())
		{
			file << m_score;
			file.close();
		}
	}
}