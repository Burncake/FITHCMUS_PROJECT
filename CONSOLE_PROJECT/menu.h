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
	static void modeSelection();
	static void menuSelection();
	static void drawGameMode(int selectedMode);
	static void printModeBoard();
	//static void mainMenu();		
	//static void loadScreen();					
	//static void playMenu();						
	static void helpScreen();	
	static void aboutScreen();
	//static void exitScreen();			
	//static void playPvP();							
	//static void playPvC1();								
	//static void playPvC2();								
	static void printLogo();		
	static void printOptionsBoard();
	static void clearConsole();
	static void printRectangle(int left, int top, int width, int height); 
	static void mainScreen();
};