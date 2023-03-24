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
#define consoleR 119
#define consoleD 29

static int setC = 60, setR = 15;

class game {
public:
	string x_player{}, o_player{};
	int x_score = 0, o_score = 0, x_count = 0, o_count = 0, x = 0, y = 0;
	int board[size][size]{};
	bool x_turn = true;
	

	static void game_pvp();
	static void drawBoard();
	static void draw_txt(string name, int x, int y, int color);
	static void drawInstruct();
	static void drawInformation();
	void showTurn();
	void move();
	void processBoard();
	bool win();
	bool draw();
	void score();
	void showScore();
	void endEffect();
	void x_win_effect();
	void o_win_effect();
	void draw_effect();
	void resetData();
	void askContinuePlay(int &key);
};
