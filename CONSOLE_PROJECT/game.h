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
static int setC = 60, setR = 15;

class game {
public:
	int x_score = 0, o_score = 0, x_count = 0, o_count = 0, x = 0, y = 0, value = 0, pos_i = -1, pos_j = -1;
	int board[size][size] = {};
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
	void saveGame(string file);
	void loadGame(string file);
	int minimax(bool isMaxiPlayer, int depth, int alpha, int beta);
	//void dummyBoard();
	void findBestMove(int& pos_i, int& pos_j);
	void pveMove();
	static void game_pve();
	void processBoardPveX();
	void processBoardPveO();

	int evaluate();

	int evaluateCell(int row, int col, int move);

	bool checkWinScore(int row, int col, int move);


	int evaluateCellDef(int row, int col, int move);

	

};
