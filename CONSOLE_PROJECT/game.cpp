#include "game.h"

void game::game_pvp()
{
	game g;
	int key = -1;
	do {
		system("cls");
		common::setUpConsole();
		system("color F0");
		drawBoard();
		drawInformation();
		common::playSound(Start);
		g.showScore();
		while (!g.win() && !g.draw()) {
			g.showTurn();
			g.move();
		}
		g.score();
		g.showScore();
		system("cls");
		g.endEffect();
		g.getContinuePlay(key);
		if (key == 9) g.resetData();
	} while (key == 9);
	if (key == 10) {
		system("cls");
		common::setUpConsole();
		system("color F0");
		drawBoard();
		drawInformation();
		common::playSound(Start);
		g.showScore();
		key = getInput();
		if (key == 9) g.game_pvp();
	}
}

void game::drawBoard()
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

void game::draw_txt(string name, int x, int y, int color)
{
	ifstream pic(loc + name + ".txt");
	if (!pic) return;
	string line;
	while (getline(pic, line)) {
		common::gotoXY(x, y++);
		coutColored(line, color);
	}
	pic.close();
}

void game::clLogoX() {
	int i = setC, j = setR - setR;
	ifstream xLogo("logoX.txt");
	if (!xLogo) return;
	string line;
	while (getline(xLogo, line)) {
		common::gotoXY(i, j);
		coutColored(line, Red);
		++j;
	}
	xLogo.close();
}
void game::clLogoO() {
	int i = setC + 31, j = setR - setR;
	ifstream oLogo("logoO.txt");
	if (!oLogo) return;
	string line;
	while (getline(oLogo, line)) {
		common::gotoXY(i, j);
		coutColored(line, Blue);
		++j;
	}
	oLogo.close();
}
void game::logoX() {
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
void game::logoO() {
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

void game::drawInstruct() {
	common::gotoXY(setC + 3, setR + 10);
	coutColored("FILL IN", 240);

	for (int i = 1; i <= iSizeC; ++i) {
		for (int j = 1; j <= iSizeR; ++j) {
			common::gotoXY(setC + i, setR + j + 8);
			switch (i) {
			case 1:
				if (j == 1)					coutColored(201, 240);
				else if (j == iSizeR)		coutColored(200, 240);
				else						coutColored(186, 240);
				break;
			case iSizeC:
				if (j == 1)					coutColored(187, 240);
				else if (j == iSizeR)		coutColored(188, 240);
				else						coutColored(186, 240);
				break;
			default:
				if (j == 1 || j == iSizeR)	coutColored(205, 240);
			}
		}
	}
}

void game::drawInformation() {
	int xC = 0, oC = 0;
	clLogoX();
	logoO();
	drawInstruct();
	for (int i = 1; i <= dSizeC; ++i) {
		for (int j = 1; j <= dSizeR; ++j) {
			common::gotoXY(i + setC, j + setR);

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
				if (i <= 10 || i >= 41)
					if (j == 1 || j == dSizeR)  coutColored(205, Black);
			}
		}
	}
	for (int i = 1; i <= 23; ++i) {
		common::gotoXY(25 + setC, i);
		coutColored(186, Black);
	}

	common::gotoXY(21 + setC, 3 + setR); coutColored("S C O R E ", Black);
	common::gotoXY(21 + setC, 6 + setR); coutColored(" M O V E ", Black);

}

void game::showTurn() {
	common::gotoXY(setC + 7, setR + 6);
	coutColored(to_string(x_count), Red);
	common::gotoXY(setC + 43, setR + 6);
	coutColored(to_string(o_count), Blue);
}

void game::move()
{
	int tx = x, ty = y;
	common::gotoXY(6 + 4 * x, 3 + 2 * y);
	if (board[y][x] == 0) {
		if (x_turn)		coutColored(char(120), PointerColor);
		else			coutColored(char(248), PointerColor);
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
		processBoard();
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

void game::processBoard() {

	if (board[y][x]) return;
	if (x_turn) {
		board[y][x] = 1;
		x_count++;
		logoX();
		clLogoO();
		x_turn = false;
	}
	else {
		board[y][x] = 2;
		o_count++;
		logoO();
		clLogoX();
		x_turn = true;
	}
}

bool game::win()
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

bool game::draw() {
	return (x_count + o_count == size * size);
}

void game::score() {
	if (win()) {
		if (x_turn)	o_score++;
		else		x_score++;
	}
}
void game::showScore() {
	common::gotoXY(setC + 7, setR + 3);
	coutColored(to_string(x_score), Red);
	common::gotoXY(setC + 43, setR + 3);
	coutColored(to_string(o_score), Blue);
}

void game::endEffect() {
	system("cls");
	if (win()) {
		if (x_turn) {
			o_win_effect();
		}
		else {
			x_win_effect();
		}
	}
	else draw_effect();
}

void game::x_win_effect()
{
	for (int color = 241; color < 256; color++) {
		for (int i = 0; i <= 10; i++) {
			for (int j = 0; j < 6; j++) {
				if (i >= 3 && i <= 7)
					if (j >= 1 && j <= 3) continue;
				common::gotoXY(i * 10 + 9, j * 5 + 2);
				if (color % 2)
					if (j % 2)
						if (i % 2) coutColored("X", DarkRed);
						else cout << " ";
					else
						if (i % 2 == 0) coutColored("X", DarkRed);
						else cout << " ";
				else
					if (j % 2)
						if (i % 2) cout << " ";
						else coutColored("X", DarkRed);
					else
						if (i % 2 == 0) cout << " ";
						else coutColored("X", DarkRed);
			}
		}
		if (color == DarkWhite || color == Yellow || color == DarkYellow || color == Cyan || color == White) continue;
		draw_txt("x_win", fSizeC + 10, dSizeR - 4, color);
		Sleep(400);
	}
}

void game::o_win_effect()
{
	for (int color = 241; color < 256; color++) {
		for (int i = 0; i <= 10; i++) {
			for (int j = 0; j < 6; j++) {
				if (i >= 3 && i <= 7)
					if (j >= 1 && j <= 3) continue;
				common::gotoXY(i * 10 + 9, j * 5 + 2);
				if (color % 2)
					if (j % 2)
						if (i % 2) coutColored("O", DarkBlue);
						else cout << " ";
					else
						if (i % 2 == 0) coutColored("O", DarkBlue);
						else cout << " ";
				else
					if (j % 2)
						if (i % 2) cout << " ";
						else coutColored("O", DarkBlue);
					else
						if (i % 2 == 0) cout << " ";
						else coutColored("O", DarkBlue);
			}
		}
		if (color == DarkWhite || color == Yellow || color == DarkYellow || color == Cyan || color == White) continue;
		draw_txt("o_win", fSizeC + 10, dSizeR - 4, color);
		Sleep(400);
	}
}

void game::draw_effect()
{
	for (int color = 241; color < 256; color++) {
		for (int i = 0; i <= 10; i++)
			for (int j = 0; j < 6; j++) {
				if (i >= 2 && i <= 8)
					if (j >= 1 && j <= 3) continue;
				common::gotoXY(i * 10 + 9, j * 5 + 2);
				if (color < 255) {
					if (color % 2) {
						if (j % 2) {
							if (i % 2) coutColored("X", DarkRed);
							else cout << " ";
						}
						else {
							if (i % 2 == 0) coutColored("X", DarkRed);
							else cout << " ";
						}
					}
					else {
						if (j % 2) {
							if (i % 2) cout << " ";
							else coutColored("O", DarkBlue);
						}
						else {
							if (i % 2 == 0) cout << " ";
							else coutColored("O", DarkBlue);
						}
					}
				}
				else {
					if (j % 2) {
						if (i % 2) coutColored("X", DarkRed);
						else coutColored("O", DarkBlue);
					}
					else {
						if (i % 2 == 0) coutColored("X", DarkRed);
						else coutColored("O", DarkBlue);
					}
				}
			}
		if (color == DarkWhite || color == Yellow || color == DarkYellow || color == Cyan || color == White) continue;
		draw_txt("draw", fSizeC + 7, dSizeR - 3, color);
		Sleep(400);
	}
}

void game::resetData() {
	x_count = 0; o_count = 0; x = 0; y = 0;
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			board[i][j] = 0;
		}
	}
	x_turn = true;
}

void game::getContinuePlay(int& key) {
	system("cls");
	cout << "Do you want to continue playing?";
	cout << "Press Y to play,ESC to quit";
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
	key = getInput();
	//if (i == 6) exit(0);

}



