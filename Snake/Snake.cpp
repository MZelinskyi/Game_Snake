#include "Snake.h"


Snake::Snake(int startX, int startY)
{
	body.push_back({ startX, startY });
	direction = Direction::RIGHT;
}

void Snake::move()
{
	Position head = body.front();

	switch (direction)
	{
		case Direction::UP: head.y--; 
		break;
		case Direction::DOWN: head.y++;
		break;
		case Direction::LEFT: head.x--;
		break;
		case Direction::RIGHT: head.x++;
		break;
	}

	body.insert(body.begin(), head);
	body.pop_back();
}

void Snake::ChangeDirection(Direction newDirection)
{
	direction = newDirection;
}

Position Snake::getHeadPosition() const
{
	return body.front();
}

const std::vector<Position>& Snake::getBody() const
{
	return body;
}
