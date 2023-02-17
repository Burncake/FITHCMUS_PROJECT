#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

void fixConsoleWindow();
void gotoXY(int x, int y);
void move(int board[][12], int& x, int& y, bool& XTurn);
void drawBoard();
void drawCharacter(int board[][12]);
void processBoard(int board[][12], int x, int y, bool& XTurn);