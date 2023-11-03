#include "gameField.h"

const char empty = '.';
const char head = '@';
const char tail = '#';
const char apple = '*';

void GameField::init(int height, int width)
{
	for (int i = 0; i < height; i++)
	{
		std::vector<char> row;
		for (int j = 0; j < width; j++)
		{
			row.push_back('.');
		}
		field.push_back(row);
	}
}

void GameField::setHead(int x, int y)
{
	field[y][x] = head;
}

void GameField::setTail(int x, int y)
{
	field[y][x] = tail;
}

void GameField::setApple(int x, int y)
{
	field[y][x] = apple;
}

void GameField::clearCell(int x, int y)
{
	field[y][x] = empty;
}

void GameField::print()
{
	for (std::vector<char> row : field)
	{
		for (char cell : row)
		{
			std::cout << " " << cell;
		}
		std::cout << "\n";
	}
}

std::vector<XAndY> GameField::getFreeCells()
{
	std::vector<XAndY> freeCells;
	for (int i = 0; i < field.size(); i++)
	{
		for (int j = 0; j < field[i].size(); j++)
		{
			if ((field[i][j] == empty) || (field[i][j] == apple))
			{
				XAndY cell;
				cell.X = j;
				cell.Y = i;
				freeCells.push_back(cell);
			}
		}
	}
	return freeCells;
}