#include "game.h"

int main()
{
	common::setUpConsole();
	int board[size][size]{};
	int x = 0, y = 0;
	int turnCountX = 0, turnCountO = 0;
	bool xTurn = true;
	system("color F0");
	drawBoard();
	drawDirection(xTurn);
	common::playSound(Start);
	while (!win(board, x, y) && !draw(turnCountX,turnCountO)) {
		printfTurn(turnCountX, turnCountO);
		move(board, x, y, xTurn, turnCountX, turnCountO);
	}
	system("cls");
	if (win(board, x, y)) {
		if (xTurn)  cout << "O won!\n";
		else        cout << "X won!\n";
	}
	else cout << "Draw!\n";
	
	return 0;
}

