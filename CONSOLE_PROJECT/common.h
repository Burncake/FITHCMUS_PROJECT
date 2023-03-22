#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
using namespace std;

// Colors
// From 0->15 black background, 240->255 white background
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

// Sounds
#define Background		0
#define Start			1
#define Move			2
#define Select			3
#define Win				4
#define	Lose			5
#define Draw			6

// Resources folder
#define loc "resources/"

class common {
private:
	static HWND consoleWindow;		// Handling console window
	static HANDLE consoleOutput;	// Handling console output
	static HANDLE consoleInput;		// Handling console input
public:
	static void setUpConsole();
	static void setUpWindow();
	static void disableMaximize();
	static void disableScroll();
	static void disableMouseSelect();
	static void showCursor(bool showFlag);
	static void setTitle();
	static void gotoXY(int x, int y);
	static void setColor(int color);
	static void playSound(int i);
};
void coutColored(string str, int color);
void coutColored(char chr, int color);
int getInput();
void printText(string text, int x, int y);