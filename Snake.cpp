#include "Snake.h"

const int Left = 1;
const int Right = 2;
const int Up = 3;
const int Down = 4;

const int Easy = 1;
const int Normal = 2;
const int Hard = 3;
const int HardPlus = 4;

const int minSize = 2;
const int errValue = -1;
const int calculateNew = -2;

void Snake::initSnake(int height, int width, int type)
{
	snakeHead.Y = height / 2 - 1;
	snakeHead.X = width / 2 - 1;
	snakeTail.Y = snakeHead.Y;
	snakeTail.X = snakeHead.X - 1;
	snake = { snakeHead, snakeTail };
	direction = Right;
	typeOfGame = type;
}

std::vector<XAndY> Snake::getSnakePosition()
{
	return snake;
}

XAndY errReturn()
{
	XAndY err;
	err.X = errValue;
	err.Y = errValue;
	return err;
}

XAndY calculateNewReturn()
{
	XAndY calcNew;
	calcNew.X = calculateNew;
	calcNew.Y = calculateNew;
	return calcNew;
}

XAndY crashedIntoWallEasy()
{
	return errReturn();
}

XAndY crashedIntoWallNormal(XAndY headPos, int direction, int height, int width)
{
	XAndY newPos = headPos;
	switch (direction)
	{
	case Left:
		newPos.X = width - 1;
		break;
	case Right:
		newPos.X = 0;
		break;
	case Up:
		newPos.Y = height - 1;
		break;
	case Down:
		newPos.Y = 0;
		break;
	}
	return newPos;
}

XAndY crashedIntoWallHard(XAndY headPos, int direction, int sizeOfSnake)
{
	if (sizeOfSnake <= 2)
	{
		return errReturn();
	}
	else
	{
		return calculateNewReturn();
	}
}

XAndY crashedIntoWall(int typeOfGame, XAndY headPos, int direction, int height, int width, int sizeOfSnake)
{
	switch (typeOfGame)
	{
	case Easy:
		return crashedIntoWallEasy();
		break;
	case Normal:
		return crashedIntoWallNormal(headPos, direction, height, width);
		break;
	case Hard:
		return crashedIntoWallHard(headPos, direction, sizeOfSnake);
		break;
	case HardPlus:
		return crashedIntoWallHard(headPos, direction, sizeOfSnake);
		break;
	}
}

XAndY checkCrashedIntoHimself(XAndY newHeadPos, std::vector<XAndY> snake)
{
	for (XAndY snakePart : snake)
	{
		if ((newHeadPos.X == snakePart.X) && (newHeadPos.Y == snakePart.Y) &&
			((snakePart.X != snake[snake.size() - 1].X) || (snakePart.Y != snake[snake.size() - 1].Y)))
		{
			return errReturn();
		}
	}
	return newHeadPos;
}

XAndY calculateNewHeadPos(int direction, int height, int width, XAndY OldHeadPos, std::vector<XAndY> snake, int typeOfGame, int sizeOfSnake)
{
	XAndY newHeadPos = OldHeadPos;
	switch (direction)
	{
	case Left:
		if (newHeadPos.X == 0)
		{
			newHeadPos = crashedIntoWall(typeOfGame, OldHeadPos, direction, height, width, sizeOfSnake);
			if ((newHeadPos.X < 0) && (newHeadPos.Y < 0)) return newHeadPos;
		}
		else
		{
			newHeadPos.X--;
		}
		break;
	case Right:
		if (newHeadPos.X == width - 1)
		{
			newHeadPos = crashedIntoWall(typeOfGame, OldHeadPos, direction, height, width, sizeOfSnake);
			if ((newHeadPos.X < 0) && (newHeadPos.Y < 0)) return newHeadPos;
		}
		else
		{
			newHeadPos.X++;
		}
		break;
	case Up:
		if (newHeadPos.Y == 0)
		{
			newHeadPos = crashedIntoWall(typeOfGame, OldHeadPos, direction, height, width, sizeOfSnake);
			if ((newHeadPos.X < 0) && (newHeadPos.Y < 0)) return newHeadPos;
		}
		else
		{
			newHeadPos.Y--;
		}
		break;
	case Down:
		if (newHeadPos.Y == height - 1)
		{
			newHeadPos = crashedIntoWall(typeOfGame, OldHeadPos, direction, height, width, sizeOfSnake);
			if ((newHeadPos.X < 0) && (newHeadPos.Y < 0)) return newHeadPos;
		}
		else
		{
			newHeadPos.Y++;
		}
		break;
	}

	newHeadPos = checkCrashedIntoHimself(newHeadPos, snake);
	return newHeadPos;
}

XAndY Snake::moveSnake(int height, int width)
{
	XAndY newSnakeHead = calculateNewHeadPos(direction, height, width, snakeHead, snake, typeOfGame, getSnakeSize());
	if ((newSnakeHead.X < 0) && (newSnakeHead.Y < 0)) return newSnakeHead;
	snakeHead = newSnakeHead;
	snake.insert(snake.begin(), snakeHead);
	return snakeHead;
}

XAndY Snake::removeTail()
{
	snakeTail = snake[snake.size() - 1];
	snake.pop_back();
	return snakeTail;
}

XAndY Snake::getSnakeHead()
{
	return snakeHead;
}

XAndY Snake::getSnakeTail()
{
	return snakeTail;
}

void Snake::setDirection(int Direction)
{
	if (((Direction == Left) && (Snake::direction == Right)) ||
		((Direction == Right) && (Snake::direction == Left)) ||
		((Direction == Up) && (Snake::direction == Down)) ||
		((Direction == Down) && (Snake::direction == Up))
		) return;

	direction = Direction;
}

int Snake::getDirection()
{
	return direction;
}

int Snake::getSnakeSize()
{
	return snake.size();
}