#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

void fixConsoleWindow();
void gotoXY(int x, int y);
void move(int& x, int& y);
void drawBoard(int& x, int& y);