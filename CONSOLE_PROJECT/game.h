#pragma once
#include "manager.h"

#define size 12

void drawBoard();
void move(int board[][size], int& x, int& y, bool& XTurn);
void drawCharacter(int board[][size]);
void processBoard(int board[][size], int x, int y, bool& XTurn);
bool win(int board[][size], int x, int y);
bool draw(int board[][size]);