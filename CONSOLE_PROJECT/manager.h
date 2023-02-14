#pragma once
#include <iostream>
#include <Windows.h>

using namespace std;
class manager
{
public:
	static void fixConsoleWindow();
	static void gotoXY(int x, int y);
};
void drawBoard();
