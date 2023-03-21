#pragma once
#include "common.h"
#include "game.h"
#include <iostream>
#include <string>


#include "Windows.h"
using namespace std;

class menu {
private:
	//static int current_option;			
	//const static string options[8];		

public:
	static void mainScreen();
	//static void mainMenu();		
	//static void loadScreen();					
	//static void playMenu();						
	static void helpScreen();
	static void aboutScreen();
	static void printLogo();
	static void printOptionsBoard();
	static void drawGameMode();
	static void printModeBoard();
	//static void exitScreen();																
	static void clearConsole();
	static void printRectangle(int left, int top, int width, int height);

	//static void playPvP();							
	//static void playPvC1();								
	//static void playPvC2();								
};