#pragma once
#include "common.h"
#include "game.h"
#include "file.h"
#include <iostream>
#include <string>
#include "Windows.h"
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
	static void setting(bool* music);
	static void exitScreen(int selectedOption, int& x, int& y);
	static void exitSelection();
	static void printOptionsBoard();

};
//ham ve unicode
void printCharacter(wstring character, COORD point, int text_color, int background_color);