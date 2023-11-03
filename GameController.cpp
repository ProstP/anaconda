#include "GameController.h"

const int errValue = -1;
const int calculateNew = -2;

const int Easy = 1;
const int Normal = 2;
const int Hard = 3;
const int HardPlus = 4;

const int Left = 1;
const int Right = 2;
const int Up = 3;
const int Down = 4;

void GameController::initGame(int setHeight, int setWidth)
{
	typeOfGame = Easy;
	height = setHeight;
	width = setWidth;
	field.init(height, width);
	snake.initSnake(height, width, typeOfGame);
	XAndY HeadSnake = snake.getSnakeHead();
	XAndY TailSnake = snake.getSnakeTail();
	field.setHead(HeadSnake.X, HeadSnake.Y);
	field.setTail(TailSnake.X, TailSnake.Y);
	createApple();
}

void GameController::printField()
{
	field.print();
}

void GameController::changeDir(int dir)
{
	snake.setDirection(dir);
}

void GameController::createApple()
{
	if (snake.getSnakeSize() == (height * width)) return;

	std::vector<XAndY> freeCells = field.getFreeCells();
	int index = rand() % freeCells.size();

	AppleX = freeCells[index].X;
	AppleY = freeCells[index].Y;
	field.setApple(AppleX, AppleY);
}

int newDirection(std::vector<XAndY> freeCells, XAndY snakeHead)
{
	for (XAndY cell : freeCells)
	{
		if ((cell.X == snakeHead.X) && (cell.Y + 1 == snakeHead.Y)) return Up;
		if ((cell.X + 1 == snakeHead.X) && (cell.Y == snakeHead.Y)) return Left;
		if ((cell.X - 1 == snakeHead.X) && (cell.Y == snakeHead.Y)) return Right;
		if ((cell.X == snakeHead.X) && (cell.Y - 1 == snakeHead.Y)) return Down;
	}
	return errValue;
}

void GameController::moveSnake()
{
	XAndY snakeHeadOld = snake.getSnakeHead();
	XAndY snakeHeadNew = snake.moveSnake(height, width);
	if ((snakeHeadNew.X == calculateNew) && (snakeHeadNew.Y == calculateNew))
	{
		if (typeOfGame == Hard)
		{
			switch (snake.getDirection())
			{
			case Left:
				snake.setDirection(Down);
				break;
			case Right:
				snake.setDirection(Up);
				break;
			case Up:
				snake.setDirection(Left);
				break;
			case Down:
				snake.setDirection(Right);
				break;
			}
		}
		else
		{
			int newDir = newDirection(field.getFreeCells(), snakeHeadOld);
			if (newDir == -1)
			{
				snakeHeadNew.X = errValue;
				snakeHeadNew.Y = errValue;
				GameController::isLiving = false;
				return;
			}
			snake.setDirection(newDir);
		}
		XAndY snakeTail = snake.removeTail();
		field.clearCell(snakeTail.X, snakeTail.Y);
		snakeHeadNew = snake.moveSnake(height, width);
	}
	if ((snakeHeadNew.X < 0) && (snakeHeadNew.Y < 0))
	{
		GameController::isLiving = false;
		return;
	}
	if ((snakeHeadNew.X == AppleX) && (snakeHeadNew.Y == AppleY))
	{
		createApple();
	}
	else
	{
		XAndY snakeTail = snake.removeTail();
		field.clearCell(snakeTail.X, snakeTail.Y);
	}
	field.setTail(snakeHeadOld.X, snakeHeadOld.Y);
	field.setHead(snakeHeadNew.X, snakeHeadNew.Y);
	if (snake.getSnakeSize() == (height * width)) win = true;
}