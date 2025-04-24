#pragma once
#include <vector>
#include "Direction.h"

struct Position
{
	int x;
	int y;
};

class Snake
{
public:
	Snake(int startX, int startY);

	void move(bool grow = false);
	void ChangeDirection(Direction newDirection);
	Position getHeadPosition() const;
	const std::vector <Position>& getBody() const;
	Direction getDirection() const;


private:
	std::vector<Position> body;
	Direction direction;
};