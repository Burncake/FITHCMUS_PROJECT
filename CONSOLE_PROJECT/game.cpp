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

void move(int board[][size], int& x, int& y, bool& XTurn, int& xCount, int& oCount)
{
	int tx = x, ty = y;
	gotoXY(6 + 4 * x, 3 + 2 * y);
	if (board[y][x] == 0) {
		if (XTurn)  coutChrColored(char(120), PointerColor);
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
		processBoard(board, x, y, XTurn, xCount, oCount);
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

void processBoard(int board[][size], int x, int y, bool& XTurn, int& xCount, int& oCount) {

	if (board[y][x]) return;
	if (XTurn) {
		board[y][x] = 1;
		xCount++;
		logoX();
		clLogoO();
		XTurn = false;
	}
	else {
		board[y][x] = 2;
		oCount++;
		logoO();
		clLogoX();
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
	PlaySound(TEXT("backgroundmusic.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}
void drawDirection(bool& XTurn) {
	int xC = 0, oC = 0;
	clLogoX();
	logoO();
	drawInstruct();
	for (int i = 1; i <= dSizeC; ++i) {
		for (int j = 1; j <= dSizeR; ++j) {
			gotoXY(i + setC, j + setR + 3);

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
					if (j == dSizeR) coutChrColored(223, 251);
				}
			}
		}
	}
	for (int i = 1; i <= dSizeR; ++i) {
		gotoXY(25 + setC, i + setR + 3);
		coutChrColored(186, 245);
	}
	for (int i = 1; i <= dSizeR+3; ++i) {
		gotoXY(setC + 25, setR - setR + i );
		coutChrColored(186, 245);
	}
	gotoXY(21 + setC, 6 + setR); coutStrColored("S C O R E ", 245);
	gotoXY(21 + setC, 9 + setR); coutStrColored(" M O V E ", 245);

}
void printfTurn(int& xCount, int& oCount) {
	gotoXY(setC + 7, setR + 8);
	coutStrColored(to_string(xCount), 245);
	gotoXY(setC + 43, setR + 8);
	coutStrColored(to_string(oCount), 245);
}

void clLogoX() {
	int i = setC, j = setR - setR;
	ifstream xLogo("logoX.txt");
	if (!xLogo) return;
	string line;
	while (getline(xLogo, line)) {
		gotoXY(i, j);
		coutStrColored(line, DarkRed);
		++j;
	}
	xLogo.close();
}
void clLogoO() {
	int i = setC + 31, j = setR - setR;
	ifstream oLogo("logoO.txt");
	if (!oLogo) return;
	string line;
	while (getline(oLogo, line)) {
		gotoXY(i, j);
		coutStrColored(line, DarkBlue);
		++j;
	}
	oLogo.close();
}
void logoX() {
	int i = setC, j = setR - setR;
	ifstream xLogo("logoX.txt");
	if (!xLogo) return;
	string line;
	while (getline(xLogo, line)) {
		gotoXY(i, j);
		coutStrColored(line, Grey);
		++j;
	}
	xLogo.close();
}
void logoO() {
	int i = setC + 31, j = setR - setR;
	ifstream oLogo("logoO.txt");
	if (!oLogo) return;
	string line;
	while (getline(oLogo, line)) {
		gotoXY(i, j);
		coutStrColored(line, Grey);
		++j;
	}
	oLogo.close();
}

void drawInstruct() {
	gotoXY(setC + 3, setR + -1);
	coutStrColored("Press \"ESC\"   - Exit", 240);
	gotoXY(setC + 3, setR );
	coutStrColored("Press \"L\"     - Save",240);
	gotoXY(setC + 3, setR +1);
	coutStrColored("Press \"T\"     - Load",240);
	gotoXY(setC + 3, setR +2);
	coutStrColored("Press \"ENTER\" - Select",240);
	gotoXY(setC + 28, setR -1);
	coutStrColored("Press \"W\" - Move up",240);
	gotoXY(setC + 28, setR );
	coutStrColored("Press \"S\" - Move down",240);
	gotoXY(setC + 28, setR +1);
	coutStrColored("Press \"A\" - Move left",240);
	gotoXY(setC + 28, setR +2);
	coutStrColored("Press \"D\" - Move right",240);
	for (int i = 1; i <= iSizeC; ++i) {
		for (int j = 1; j <= iSizeR; ++j) {
			gotoXY(setC + i, setR + j-3);
			switch (i) {
			case 1:
				if (j == 1) coutChrColored(201, 240);
				else if (j == iSizeR) coutChrColored(200, 240);
				else coutChrColored(186, 240);
				break;
			case iSizeC:
				if (j == 1) coutChrColored(187, 240);
				else if (j == iSizeR) coutChrColored(188, 240);
				else coutChrColored(186, 240);
				break;
			default:
				if (j == 1||j==iSizeR) coutChrColored(205, 240);
			}
		}
	}
}