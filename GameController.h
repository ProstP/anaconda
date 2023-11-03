#pragma once
#include <iostream>
#include "Snake.h"
#include "GameField.h"

class GameController
{
public:
	void initGame(int height, int width);
	void printField();
	void changeDir(int dir);
	void moveSnake();
	bool isLiving;
	bool win;
private:
	void createApple();
	int AppleX;
	int AppleY;
	GameField field;
	Snake snake;
	int width;
	int height;
	int typeOfGame;
};