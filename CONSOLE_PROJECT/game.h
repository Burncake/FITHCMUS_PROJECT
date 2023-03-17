#pragma once
#include "common.h"
#include <string>
#include <MMsystem.h>
#include <thread>
#include <fstream>
#define size 12
#define dSizeC 50
#define dSizeR 8
#define iSizeC 50
#define iSizeR 3
#define fSizeC 24
#define fSizeR 13
static int setC = 60, setR = 15;
void drawBoard();
void move(int board[][size], int& x, int& y, bool& XTurn, int& xCount, int& oCount);
//void drawCharacter(int board[][size]);
void processBoard(int board[][size], int x, int y, bool& XTurn, int& xCount, int& oCount);
bool win(int board[][size], int x, int y);
bool draw(int& xCount, int& oCount);
void drawDirection(bool &XTurn);
void printfTurn(int &xCount, int &oCount);
void clLogoX();
void clLogoO();
void logoX();
void logoO();
void drawInstruct();

void drawFrame();
