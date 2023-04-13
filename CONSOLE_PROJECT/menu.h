#pragma once
#include "common.h"
#include "game.h"
#include "file.h"
#include <iostream>
#include <string>
#include "Windows.h"
#define m_manager "m_manager.txt"

class menu {
public:
	bool music = false;
	int st_color = 0, nd_color = 1;
	menu() {
		string location = loc;
		ifstream in(location + m_manager);
		if (!in) {
			in.close();
			return;
		}
		in >> music;
		in >> st_color >> nd_color;
		in.close();
	}

	// cac mau 
	int color[7] = { DarkRed, DarkBlue, DarkCyan, Cyan, DarkGreen, Pink, DarkPink };

	static void mainScreen(int selectedMenu);
	static void settingScreen(int selectedMenu, int& x, int& y, const int cursor, menu& m);
	static void modeSelection(menu& m);
	static void menuSelection(menu& m);
	static void drawGameMode(int selectedMode);
	static void printModeBoard();
	static void helpScreen();
	static void aboutScreen();
	static void setting(menu& m);
	static void exitScreen(int selectedOption, int& x, int& y);
	static void exitSelection(menu m);
	static void printOptionsBoard();
	static void saveSetting(menu m);
};
//ham ve unicode
void printCharacter(wstring character, COORD point, int text_color, int background_color);
void startMenu();