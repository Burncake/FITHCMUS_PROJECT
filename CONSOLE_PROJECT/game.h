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
#define maxDepth 5
#define pvp 1
#define pve 2
static int setC = 60, setR = 15;

class game {
public:
	int mode = 0, x_score = 0, o_score = 0, x_count = 0, o_count = 0, x = 0, y = 0, value = 0, pos_i = -1, pos_j = -1;
	int board[size][size]{};
	bool x_turn = true;
	static void game_pvp(game& g, int stcolor, int ndcolor);
	void drawBoard(int stcolor, int ndcolor);
	static void draw_txt(string name, int x, int y, int color);
	static void drawInstruct(bool viewMode);
	static void drawInformation(bool viewMode);
	void showTurn();
	void drawCursor();
	void move(int i, int stcolor, int ndcolor);
	void processBoard();
	bool win();
	bool draw();
	void score();
	void showScore();
	void endEffect();
	void x_win_effect();
	void o_win_effect();
	void botMode_end_effect();
	void player_win_effect();
	void player_lose_effect();
	void draw_effect();
	void resetData();
	void askContinuePlay(int& key);
	void saveGame(string file);
	void loadGame(string file);
	//int minimax(bool isMaxiPlayer, int depth, int alpha, int beta);
	//void dummyBoard();
	void findBestMove();
	void pveMove(int i, int stcolor, int ndcolor);
	static void game_pve(game& g, int stcolor, int ndcolor);
	void processBoardPveX();
	void processBoardPveO();
	bool checkBorder(int x, int y);
	int defendPoint(int x, int y);
	int attackPoint(int x, int y);

};
