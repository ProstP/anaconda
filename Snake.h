#pragma once
#include <iostream>
#include <vector>
#include "GameField.h"

class Snake
{
public:
	std::vector<XAndY> getSnakePosition();
	XAndY moveSnake(int height, int width);
	XAndY getSnakeHead();
	XAndY getSnakeTail();
	XAndY removeTail();
	void setDirection(int direction);
	int getDirection();
	void initSnake(int height, int width, int typeOfGame);
	int getSnakeSize();
private:
	int typeOfGame;
	int direction;
	XAndY snakeHead;
	XAndY snakeTail;
	std::vector<XAndY> snake;
};