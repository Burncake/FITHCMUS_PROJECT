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
	static void menuSelection();
			
	//static void loadScreen();					
	//static void playMenu();						
	static void helpScreen();	
	static void aboutScreen();
	static void printLogo();
	static void printOptionsBoard();
	static void drawGameMode(int selectedMode);
	static void modeSelection();
	static void printModeBoard();
	//static void exitScreen();																
	static void clearConsole();
	static void printRectangle(int left, int top, int width, int height); 
};

//------------------------------------------
