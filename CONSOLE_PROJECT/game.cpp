#include "game.h"

void drawBoard()
{
	const int endRow = 4 * size + 1, endColumn = 2 * size + 1;
	for (int i = 1; i <= endColumn; i++)
		for (int j = 1; j <= endRow; j++) {
			common::gotoXY(j + 3, i + 1);
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
	common::gotoXY(6 + 4 * x, 3 + 2 * y);
	if (board[y][x] == 0) {
		if (XTurn)  coutColored(char(120), PointerColor);
		else        coutColored(char(248), PointerColor);
	}
	if (board[y][x] == 1) coutColored("X", 178);
	if (board[y][x] == 2) coutColored("O", 181);

	int i = getInput();
	switch (i) {
	case 1:
		common::playSound(Move);
		y--;
		if (y < 0) y = size - 1;
		break;
	case 2:
		common::playSound(Move);
		x--;
		if (x < 0) x = size - 1;
		break;
	case 3:
		common::playSound(Move);
		y++;
		if (y > size - 1) y = 0;
		break;
	case 4:
		common::playSound(Move);
		x++;
		if (x > size - 1) x = 0;
		break;
	case 5:
		common::playSound(Select);
		processBoard(board, x, y, XTurn, xCount, oCount);
		break;
	}
	if (board[ty][tx] == 0) {
		common::gotoXY(6 + 4 * tx, 3 + 2 * ty);
		cout << " ";
	}
	if (board[ty][tx] == 1) {
		common::gotoXY(6 + 4 * tx, 3 + 2 * ty);
		coutColored("X", DarkRed);
	}
	if (board[ty][tx] == 2) {
		common::gotoXY(6 + 4 * tx, 3 + 2 * ty);
		coutColored("O", DarkBlue);
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

void drawDirection(bool& XTurn) {
	int xC = 0, oC = 0;
	clLogoX();
	logoO();
	drawFrame();
	drawInstruct();
	for (int i = 1; i <= dSizeC; ++i) {
		for (int j = 1; j <= dSizeR; ++j) {
			common::gotoXY(i + setC, j + setR );

			switch (i) {
			case 1:
				// Left column //
				if (j == 1)                 coutColored(201, Black);
				else if (j == dSizeR)     coutColored(200, Black);
				else                         coutColored(186, Black);
				break;
			case dSizeC:
				// Left column //
				if (j == 1)                 coutColored(187, Black);
				else if (j == dSizeR)     coutColored(188, Black);
				else                         coutColored(186, Black);
				break;
			default:
				if (i <= 10 || i >= 41) {
					if (j == 1|| j == dSizeR)  coutColored(205, Black);
				}
			}
		}
	}
	for (int i = 1; i <=23; ++i) {
		common::gotoXY(25 + setC, i );
		coutColored(186, Black);
	}
	
	common::gotoXY(21 + setC, 3 + setR); coutColored("S C O R E ", Black);
	common::gotoXY(21 + setC, 6 + setR); coutColored(" M O V E ", Black);

}
void printfTurn(int& xCount, int& oCount) {
	common::gotoXY(setC + 7, setR+6);
	coutColored(to_string(xCount), Red);
	common::gotoXY(setC + 43, setR+6);
	coutColored(to_string(oCount), Blue);
}

void clLogoX() {
	int i = setC, j = setR - setR;
	ifstream xLogo("logoX.txt");
	if (!xLogo) return;
	string line;
	while (getline(xLogo, line)) {
		common::gotoXY(i, j);
		coutColored(line, DarkRed);
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
		common::gotoXY(i, j);
		coutColored(line, DarkBlue);
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
		common::gotoXY(i, j);
		coutColored(line, Grey);
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
		common::gotoXY(i, j);
		coutColored(line, Grey);
		++j;
	}
	oLogo.close();
}

void drawInstruct() {
	common::gotoXY(setC + 3, setR + 10);
	coutColored("FILL IN", 240);
	
	for (int i = 1; i <= iSizeC; ++i) {
		for (int j = 1; j <= iSizeR; ++j) {
			common::gotoXY(setC + i, setR + j + 8);
			switch (i) {
			case 1:
				if (j == 1) coutColored(201, 240);
				else if (j == iSizeR) coutColored(200, 240);
				else coutColored(186, 240);
				break;
			case iSizeC:
				if (j == 1) coutColored(187, 240);
				else if (j == iSizeR) coutColored(188, 240);
				else coutColored(186, 240);
				break;
			default:
				if (j == 1 || j == iSizeR) coutColored(205, 240);
			}
		}
	}
}
void drawFrame() {
	for (int i = 1; i <= fSizeC; ++i) {
		for (int j = 1; j <= fSizeR; ++j) {
			common::gotoXY(setC + i-3,j+1);
			switch (i) {
			case 1:
				if (j == 1) coutColored(201, Red);
				else if (j == fSizeR) coutColored(200, Red);
				else coutColored(186, Red);
				break;
			case fSizeC:
				if (j == 1) coutColored(187, Red);
				else if (j == fSizeR) coutColored(188, Red);
				else coutColored(186, Red);
				break;
			default:
				if (j == 1 || j == fSizeR) coutColored(205, Red);
			}
		}
	}
}