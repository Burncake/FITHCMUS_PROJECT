#include "game.h"

void drawBoard()
{
	const int endRow = 4 * size + 1, endColumn = 2 * size + 1;
	for (int i = 1; i <= endColumn; i++)
		for (int j = 1; j <= endRow; j++) {
			gotoXY(j + 3, i + 1);
			switch (j) {
			case 1:
				// Left column //
				if (i == 1)                 cout << char(218);
				else if (i == endColumn)    cout << char(192);
				else if ((i - 1) % 2 == 0)  cout << char(195);
				else                        cout << char(179);
				break;
			case endRow:
				// Right column //
				if (i == 1)                 cout << char(191);
				else if (i == endColumn)    cout << char(217);
				else if ((i - 1) % 2 == 0)  cout << char(180);
				else                        cout << char(179);
				break;
			default:
				if ((j - 1) % 4 == 0) {
					if (i == 1)                 cout << char(194);
					else if (i == endColumn)    cout << char(193);
					else if ((i - 1) % 2 == 0)  cout << char(197);
					else                        cout << char(179);
				}
				else if (i % 2) cout << char(196);
				else            cout << " ";
			}
			cout << endl;
		}

}

void move(int board[][size], int& x, int& y, bool& XTurn)
{
	int tx = x, ty = y;
	gotoXY(6 + 4 * x, 3 + 2 * y);
	if (board[y][x] == 0) {
		if (XTurn)  coutChrColored(char(42), PointerColor);
		else        coutChrColored(char(248), PointerColor);
	}
	if (board[y][x] == 1) coutStrColored("X", 178);
	if (board[y][x] == 2) coutStrColored("O", 181);

	char c;
	c = _getch();
	switch (c) {
	case 'w':
		moveSound();
		y--;
		if (y < 0) y = size - 1;
		break;
	case 'a':
		moveSound();
		x--;
		if (x < 0) x = size - 1;
		break;
	case 's':
		moveSound();
		y++;
		if (y > size - 1) y = 0;
		break;
	case 'd':
		moveSound();
		x++;
		if (x > size - 1) x = 0;
		break;
	case '\r':
		selectSound();
		processBoard(board, x, y, XTurn);
		break;
	}
	if (board[ty][tx] == 0) {
		gotoXY(6 + 4 * tx, 3 + 2 * ty);
		cout << " ";
	}
	if (board[ty][tx] == 1) {
		gotoXY(6 + 4 * tx, 3 + 2 * ty);
		coutStrColored("X", DarkRed);
	}
	if (board[ty][tx] == 2) {
		gotoXY(6 + 4 * tx, 3 + 2 * ty);
		coutStrColored("O", DarkBlue);
	}
}

void processBoard(int board[][size], int x, int y, bool& XTurn) {
	if (board[y][x]) return;
	if (XTurn) {
		board[y][x] = 1;
		XTurn = false;
	}
	else {
		board[y][x] = 2;
		XTurn = true;
	}
}

bool win(int board[][size], int x, int y)
{
	int countR = 0, countD = 0, countUR = 0, countDR = 0;
	for (int i = -4; i < 5; i++) {
		if (!board[y][x]) break;
		if ((x + i >= 0) && (x + i <= size - 1)) {
			if (board[y][x] == board[y][x + i]) countR++;
			else countR = 0;
		}
		if ((y + i >= 0) && (y + i <= size - 1)) {
			if (board[y][x] == board[y + i][x]) countD++;
			else countD = 0;
		}
		if ((x + i >= 0) && (x + i <= size - 1) && (y + i >= 0) && (y + i <= size - 1)) {
			if (board[y][x] == board[y + i][x + i]) countDR++;
			else countDR = 0;
		}
		if ((x + i >= 0) && (x + i <= size - 1) && (y - i >= 0) && (y - i <= size - 1)) {
			if (board[y][x] == board[y - i][x + i]) countUR++;
			else countUR = 0;
		}
		if ((countR == 5) || (countD == 5) || (countDR == 5) || (countUR == 5)) return true;
	}
	return false;
}

bool draw(int& xCount, int& oCount) {
	return(xCount + oCount == size * size);
}
void moveSound() {
	PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
void selectSound() {
	PlaySound(TEXT("select.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
void bgSound() {
	PlaySound(TEXT("backgroundmusic.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
void drawDirection(bool &XTurn) {
	int xC = 0, oC = 0;
	
	for (int i = 1; i <= dSizeC; ++i) {
		for (int j = 1; j <= dSizeR; ++j) {
			gotoXY(i + setC, j + setR);

			switch (i) {
			case 1:
				// Left column //
				if (j == 1)                 coutChrColored(220, 251);
				else if (j == dSizeR)     coutChrColored(223, 251);
				else                         coutChrColored(219, 251);
				break;
			case dSizeC:
				// Left column //
				if (j == 1)                 coutChrColored(220, 251);
				else if (j == dSizeR)     coutChrColored(223, 251);
				else                         coutChrColored(219, 251);
				break;
			default:
				if (i <= 10 || i >= 41) {
					if (j == 1)  coutChrColored(220, 251);
					if(j==dSizeR) coutChrColored(223, 251);
				}
			}
		}
	}
	for (int i = 1; i <= 11; ++i) {
		gotoXY(25 + setC, i + setR);
		coutChrColored(186, 245);
	}
	gotoXY(21 + setC, 4 + setR); coutStrColored("S C O R E ", 245);
	gotoXY(21 + setC, 8 + setR); coutStrColored(" M O V E ", 245);
	
}
void countTurn(int board[][size],int &xCount, int &oCount,int x,int y,bool &XTurn) {

	if (board[y][x] == 1&&(!XTurn)) {
		xCount++;
		if (xCount - oCount == 2) xCount--;
	}
	if (board[y][x] == 2&&XTurn) {
		oCount++;
		if (oCount - xCount == 1) oCount--;
	}
	
}
void printfTurn(int &xCount, int &oCount) {
	gotoXY(setC + 7, setR + 8);
	coutStrColored(to_string(xCount), 245);
	gotoXY(setC + 43, setR + 8);
	coutStrColored(to_string(oCount), 245);
}