#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
using namespace std;

// Colors.
#define DEFAULTCOLOR	240
#define PointerColor	246

#define Black			240
#define DarkBlue		241
#define DarkGreen		242
#define DarkCyan		243
#define DarkRed			244
#define DarkPink		245
#define DarkYellow		246
#define DarkWhite		247
#define Grey			248
#define Blue			249
#define Green			250
#define Cyan			251
#define Red				252
#define Pink			253
#define Yellow			254
#define White			255
// From 0->15 black background, 240->255 white background.

void fixConsoleWindow();
void gotoXY(int x, int y);
void setColor(int color);
void coutStrColored(string str, int color);
void coutChrColored(char chr, int color);