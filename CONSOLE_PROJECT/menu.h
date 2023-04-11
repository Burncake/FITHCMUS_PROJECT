#pragma once
#include "common.h"
#include "game.h"
#include <iostream>
#include <string>
#include "Windows.h"
using namespace std;

class menu {

public:
	static void mainScreen(int selectedMenu);
	static void settingScreen(int selectedMenu, int& x, int& y, const int cursor);
	static void modeSelection();
	static void menuSelection();
	static void drawGameMode(int selectedMode);
	static void printModeBoard();					
	static void helpScreen();
	static void aboutScreen();
	static void setting();
	static void exitScreen(int selectedOption, int& x, int& y);
	static void exitSelection();
	static void printLogo();
	static void bigOScreen();
	static void bigXScreen();
	static void particles();
	static void printOptionsBoard();
	static void clearConsole();
	static void printRectangle(int left, int top, int width, int height);

};
//ham ve unicode
void printCharacter(wstring character, COORD point, int text_color, int background_color);