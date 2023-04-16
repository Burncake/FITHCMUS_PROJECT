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
#define DarkBlue		241 //
#define DarkGreen		242 // Green
#define DarkCyan		243 //
#define DarkRed			244 //
#define DarkPink		245 // Purple
#define DarkYellow		246 
#define DarkWhite		247
#define Grey			248
#define Blue			249
#define Green			250
#define Cyan			251 // Cyan
#define Red				252
#define Pink			253 // Pink
#define Yellow			254
#define White			255

#define blackRed		64
#define blackCyan		176
#define redCyan			180
#define whiteBlack		7

// Sounds
#define Start			0
#define Move			1
#define Select			2
#define Win				3
#define	Lose			4
#define Draw			5

//drawPixel
#define pixel			219
#define pixelDown		220
#define pixelUp			223

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
	static void bgmusic(bool n);
	static void playSound(int i);
	static void changeFont();
};
void coutColored(string str, int color);
void coutColored(char chr, int color);
int getInput();
void printText(string text, int x, int y);
void clearConsole();
void printRectangle(int left, int top, int width, int height);
void putcharXY(int ch, int x, int y);
void drawLogoPixelXY(int ch, int x, int y);
void drawLogoPixel(int ch, unsigned char pix[]);
void drawSymbolPixel(int ch, unsigned char pix[], int x, int y);
void drawXY(int color, int ch, int x, int y);
void drawRowPixel(int color, int ch, int num, int x, int y);

void printLogo();
void bigOScreen();
void bigXScreen();
void particles();