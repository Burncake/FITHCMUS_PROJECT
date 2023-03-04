#pragma once
#include "manager.h"
#include <string>
#include <MMsystem.h>
#include <thread>
#include <fstream>
#define size 12
#define dSizeC 50
#define dSizeR 11
static int setC = 60, setR = 15;
void drawBoard();
void move(int board[][size], int& x, int& y, bool& XTurn);
//void drawCharacter(int board[][size]);
void processBoard(int board[][size],  int x, int y, bool& XTurn);

bool win(int board[][size], int x, int y);
bool draw(int& xCount, int& oCount);
void moveSound();
void selectSound();
void bgSound();
void drawDirection(bool &XTurn);
void countTurn(int board[][size], int& xCount, int& oCount, int x, int y, bool& XTurn);
void printfTurn(int &xCount, int &oCount);
void clLogoX();
void clLogoO();
void logoX();
void logoO();
void processTurn(bool& XTurn);