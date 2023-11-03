#include <iostream>
#include "GameController.h"
#include <windows.h>
#include <conio.h>

const int width = 8;
const int height = 8;

const int Left = 1;
const int Right = 2;
const int Up = 3;
const int Down = 4;

const int firstCode = 224;
const int ArrowUp = 72;
const int ArrowDown = 80;
const int ArrowLeft = 75;
const int ArrowRight = 77;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	GameController controller;
	controller.isLiving = true;
	controller.initGame(height, width);
	controller.printField();

	_getch();
	while (controller.isLiving)
	{
		controller.moveSnake();
		if (!controller.isLiving)
		{
			break;
		}
		if (controller.win)
		{
			system("cls");
			controller.printField();
			std::cout << "Молодец, ты победил!!!!";
			break;
		}
		system("cls");
		controller.printField();

		Sleep(500);

		if (!_kbhit())
		{
			continue;
		}

		int command = _getch();
		if (command == firstCode)
		{
			command = _getch();
		}
		switch (command)
		{
		case ArrowLeft:
			controller.changeDir(Left);
			break;
		case ArrowRight:
			controller.changeDir(Right);
			break;
		case ArrowUp:
			controller.changeDir(Up);
			break;
		case ArrowDown:
			controller.changeDir(Down);
			break;
		}
	}
}