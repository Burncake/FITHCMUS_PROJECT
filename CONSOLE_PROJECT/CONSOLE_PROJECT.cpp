#include "game.h"

int main()
{
	bgSound();
	fixConsoleWindow();
	int board[size][size]{};
	int x = 0, y = 0;
	int cX = 0, cO = 0;
	bool XTurn = true;
	system("color F0");
	drawBoard();
	drawDirection(XTurn);
	while (!win(board, x, y) && !draw(cX,cO)) {
		
		printfTurn(cX, cO);
		move(board, x, y, XTurn);
		countTurn(board, cX, cO, x, y, XTurn);
	}
	system("cls");
	system("color 0F");
	if (win(board, x, y)) {
		if (XTurn)  cout << "O won!\n";
		else        cout << "X won!\n";
	}
	else cout << "Draw!\n";
	
	return 0;
}

