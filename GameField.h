#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

struct XAndY
{
	int X;
	int Y;
};

class GameField
{
public:
	void init(int height, int width);
	void print();
	void setHead(int x, int y);
	void setTail(int x, int y);
	void setApple(int, int y);
	void clearCell(int x, int y);
	std::vector<XAndY> getFreeCells();
private:
	std::vector<std::vector<char>> field;
};