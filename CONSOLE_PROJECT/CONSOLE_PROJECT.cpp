#include "game.h"

int main()
{
	int board[size][size]{ 0 };
	int x = 0, y = 0, count = 0;
	bool XTurn = true;
	bool draw=false;
	system("color F0");
	drawBoard();
	while (!win(board, x, y)) {
		drawCharacter(board);
		move(board, x, y, XTurn, count);
		if (checkFullBoard(count)) {
			draw = true;
			break;
		}
	}
	system("cls");
	system("color 0F");
	if (draw) {
		cout << "DRAW";
	}
	else {
		if (XTurn)  cout << "O won!\n";
		else        cout << "X won!\n";
	}
	return 0;
}

