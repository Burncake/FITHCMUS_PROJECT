#include "game.h"
#include "file.h"
int attackEvaluate[5] = { 0, 800, 100000, 1000000, 1000000000 };
int defendEvaluate[5] = { 0, 800, 100000, 1000000,400000000 };

void game::bootGame(game& g, int stcolor, int ndcolor, bool music)
{
	int key = 0;
	while (false == false) {
		while (!key) {
			if (g.mode == pvp) key = game::game_pvp(g, stcolor, ndcolor);
			if (g.mode == pvc) key = game::game_pve(g, stcolor, ndcolor);
		}
		if (key == -1) return;
		g.score();
		g.showScore();
		if (g.mode == pvp) g.endEffect(key, music);
		if (g.mode == pvc) g.botMode_end_effect(key, music);
		do {
			g.askContinuePlay(key);
			if (key == 6) {
				common::playSound(Select);
				return;
			}
			if (key == 9) {
				g.resetData();
				key = -1;
				break;
			}
			if (key == 10) {
				common::playSound(Select);
				clearConsole();
				g.drawBoard(stcolor, ndcolor);
				drawInformation(true, stcolor, ndcolor);
				g.showTurn();
				g.showScore();
				while (false == false) {
					key = getInput();
					if (key == 6) {
						common::playSound(Select);
						return;
					}
					if (key == 9) {
						g.resetData();
						key = -1;
						break;
					}
				}
				break;
			}
		} while (key != 6 && key != 9 && key != 10);
		key = 0;
	}
}

int game::game_pvp(game& g, int stcolor, int ndcolor)
{
	int key = -1;
	clearConsole();
	g.drawBoard(stcolor, ndcolor);
	drawInformation(false, stcolor, ndcolor);
	common::playSound(Start);
	g.showScore();
	int flag = g.win();
	while (!flag && !g.draw()) {
		g.showTurn();
		g.drawCursor();
		key = getInput();
		g.move(key, stcolor, ndcolor);
		if (key == 6) {
			common::playSound(Select);
			clearConsole();
			printRectangle(40, 12, 34, 2);
			printText("Do you want to save? (Y/N)", 45, 13);
			while (false == false) {
				key = getInput();
				if (key == 9) {
					file::saveScreen(g);
					return 0;
				}
				if (key == 10) {
					common::playSound(Select);
					return -1;
				}
			}
		}
		if (key == 7) {
			file::saveScreen(g);
			return 0;
		}
		if (key == 8) {
			file::loadScreen(g);
			return 0;
		}
		flag = g.win();
	}
	return flag;
}

	void game::drawBoard(int stcolor, int ndcolor)
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
	for (int ty = 0; ty < size; ty++) {
		for (int tx = 0; tx < size; tx++) {
			common::gotoXY(6 + 4 * tx, 3 + 2 * ty);
			if (board[ty][tx] == 1) coutColored("X", stcolor);
			if (board[ty][tx] == 2) coutColored("O", ndcolor);
		}
	}
}

void game::draw_txt(string name, int x, int y, int color)
{
	ifstream pic(loc + name);
	if (!pic) return;
	string line;
	while (getline(pic, line)) {
		common::gotoXY(x, y++);
		coutColored(line, color);
	}
	pic.close();
}

void game::drawInstruct(bool viewMode) {
	common::gotoXY(setC + 4, setR + 10);
	if (viewMode) coutColored("'Y': Start a new game\t 'ESC': Back to menu", 240);
	else coutColored("'L': Save\t 'T': Load\t 'ESC': Menu", 240);

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

void game::drawInformation(bool viewMode, int stcolor, int ndcolor) {
	int xC = 0, oC = 0;
	drawlogoX(true, setC, 3, stcolor);
	drawlogoO(false, setC + 29, 3, ndcolor);
	drawInstruct(viewMode);
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
	for (int i = 3; i <= 23; ++i) {
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

void game::drawCursor()
{
	common::gotoXY(6 + 4 * x, 3 + 2 * y);
	if (board[y][x] == 0) {
		if (x_turn)		coutColored(char(120), PointerColor);
		else			coutColored(char(248), PointerColor);
	}
	if (board[y][x] == 1) coutColored("X", 178);
	if (board[y][x] == 2) coutColored("O", 181);
}

void game::move(int i, int stcolor, int ndcolor)
{
	int tx = x, ty = y;
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
		processBoard(stcolor, ndcolor);
		break;
	}
	if (board[ty][tx] == 0) {
		common::gotoXY(6 + 4 * tx, 3 + 2 * ty);
		cout << " ";
	}
	if (board[ty][tx] == 1) {
		common::gotoXY(6 + 4 * tx, 3 + 2 * ty);
		coutColored("X", stcolor);
	}
	if (board[ty][tx] == 2) {
		common::gotoXY(6 + 4 * tx, 3 + 2 * ty);
		coutColored("O", ndcolor);
	}
}

void game::processBoard(int stcolor, int ndcolor) {

	if (board[y][x]) return;
	if (x_turn) {
		board[y][x] = 1;
		x_count++;
		x_turn = false;
		drawlogoX(x_turn, setC, 3, stcolor);
		drawlogoO(!x_turn, setC + 29, 3, ndcolor);
	}
	else {
		board[y][x] = 2;
		o_count++;
		x_turn = true;
		drawlogoO(!x_turn, setC + 29, 3, ndcolor);
		drawlogoX(x_turn, setC, 3, stcolor);
	}
}
int game::win()
{
	int countR = 0, countD = 0, countUR = 0, countDR = 0;
	for (int m = 0; m < size; m++) {
		for (int n = 0; n < size; n++) {
			countR = 0, countD = 0, countUR = 0, countDR = 0;
			for (int i = -4; i < 5; i++) {
				if (!board[m][n]) {
					break;
				}
				if ((n + i >= 0) && (n + i <= size - 1)) {
					if (board[m][n] == board[m][n + i]) countR++;
					else countR = 0;
				}
				if ((m + i >= 0) && (m + i <= size - 1)) {
					if (board[m][n] == board[m + i][n]) countD++;
					else countD = 0;
				}
				if ((n + i >= 0) && (n + i <= size - 1) && (m + i >= 0) && (m + i <= size - 1)) {
					if (board[m][n] == board[m + i][n + i]) countDR++;
					else countDR = 0;
				}
				if ((n + i >= 0) && (n + i <= size - 1) && (m - i >= 0) && (m - i <= size - 1)) {
					if (board[m][n] == board[m - i][n + i]) countUR++;
					else countUR = 0;
				}
				if (countR == 5) {
					x = n + i;
					y = m;
					return 1;
				}
				if (countD == 5) {
					x = n;
					y = m + i;
					return 2;
				}
				if (countDR == 5) {
					x = n + i;
					y = m + i;
					return 3;
				}
				if (countUR == 5) {
					x = n + i;
					y = m - i;
					return 4;
				}
			}
		}
	}
	return 0;
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

void game::endEffect(int flag, bool bgmusic) {
	int fix_x = 0, fix_y = 0;
	if (flag == 1) {
		fix_x = -1;
		fix_y = 0;
	}
	if (flag == 2) {
		fix_x = 0;
		fix_y = -1;
	}
	if (flag == 3) {
		fix_x = -1;
		fix_y = -1;
	}
	if (flag == 4) {
		fix_x = -1;
		fix_y = 1;
	}
	for (int time = 1; time < 3; time++) {
		for (int color = 241; color < 256; color++) {
			if (color == DarkWhite || color == Yellow || color == DarkYellow || color == Cyan || color == White) continue;
			for (int i = 0; i < 5; i++) {
				common::gotoXY(6 + 4 * (x + fix_x * i), 3 + 2 * (y + fix_y * i));
				if (board[y + fix_y * i][x + fix_x * i] == 1) coutColored("X", color);
				if (board[y + fix_y * i][x + fix_x * i] == 2) coutColored("O", color);
				Sleep(50);
			}
		}
	}
	clearConsole();
	if (win()) {
		if (x_turn) {
			o_win_effect();
		}
		else {
			x_win_effect();
		}
	}
	else draw_effect(bgmusic);
}

void game::x_win_effect()
{
	common::playSound(Win);
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
		draw_txt("x_win.txt", fSizeC + 10, dSizeR - 4, color);
		Sleep(400);
	}
}

void game::o_win_effect()
{
	common::playSound(Win);
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
		draw_txt("o_win.txt", fSizeC + 10, dSizeR - 4, color);
		Sleep(400);
	}
}

void game::botMode_end_effect(int flag, bool bgmusic)
{
	int fix_x = 0, fix_y = 0;
	if (flag == 1) {
		fix_x = -1;
		fix_y = 0;
	}
	if (flag == 2) {
		fix_x = 0;
		fix_y = -1;
	}
	if (flag == 3) {
		fix_x = -1;
		fix_y = -1;
	}
	if (flag == 4) {
		fix_x = -1;
		fix_y = 1;
	}
	for (int time = 1; time < 3; time++) {
		for (int color = 241; color < 256; color++) {
			if (color == DarkWhite || color == Yellow || color == DarkYellow || color == Cyan || color == White) continue;
			for (int i = 0; i < 5; i++) {
				common::gotoXY(6 + 4 * (x + fix_x * i), 3 + 2 * (y + fix_y * i));
				if (board[y + fix_y * i][x + fix_x * i] == 1) coutColored("X", color);
				if (board[y + fix_y * i][x + fix_x * i] == 2) coutColored("O", color);
				Sleep(50);
			}
		}
	}
	clearConsole();
	if (win()) {
		if (x_turn) {
			player_lose_effect(bgmusic);
		}
		else {
			player_win_effect();
		}
	}
	else draw_effect(bgmusic);
}
void game::player_win_effect() {
	common::playSound(Win);
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
		draw_txt("player_win.txt", fSizeC + 10, dSizeR - 4, color);
		Sleep(400);
	}
}
void game::player_lose_effect(bool bgmusic) {
	common::bgmusic(false);
	common::playSound(Lose);
	for (int color = 241; color < 256; color++) {
		if (color == DarkWhite || color == Yellow || color == DarkYellow || color == Cyan || color == White) continue;
		draw_txt("player_lose.txt", fSizeC + 4, dSizeR - 4, color);
		Sleep(500);
	}
	common::bgmusic(bgmusic);
}

void game::draw_effect(bool bgmusic)
{
	common::bgmusic(false);
	common::playSound(Draw);
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
		draw_txt("draw.txt", fSizeC + 7, dSizeR - 3, color);
		Sleep(400);
	}
	common::bgmusic(bgmusic);
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

void game::askContinuePlay(int& key) {
	printRectangle(42, 21, 32, 4);
	printText(" Press Y to continue ", 49, 22);
	printText("Press N to review the game", 46, 23);
	printText("Press ESC to turn back to menu", 44, 24);
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
	key = getInput();
}

void game::saveGame(string file)
{
	ofstream game(file);
	if (!game) return;
	game << mode << endl;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			game << board[i][j] << " ";
		}
		game << endl;
	}
	game << x_score << " " << o_score << endl;
	game << x << " " << y << endl;
	game << value << " " << pos_i << " " << pos_j << endl;
	game.close();
}
void game::loadGame(string file) {
	ifstream game(file);
	x_count = o_count = 0;
	game >> mode;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			game >> board[i][j];
			if (board[i][j] == 1)		x_count++;
			else if (board[i][j] == 2)	o_count++;
		}
	}
	game >> x_score >> o_score;
	game >> x >> y;
	game >> value >> pos_i >> pos_j;
	x_turn = (x_count == o_count);
	game.close();
}


void game::pveMove(int i, int stcolor, int ndcolor) {
	int tx = x, ty = y;
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
		processBoardPveX(stcolor, ndcolor);
		break;
	}
	if (board[ty][tx] == 0) {
		common::gotoXY(6 + 4 * tx, 3 + 2 * ty);
		cout << " ";
	}
	if (board[ty][tx] == 1) {
		common::gotoXY(6 + 4 * tx, 3 + 2 * ty);
		coutColored("X", stcolor);
	}
	if (board[ty][tx] == 2) {
		common::gotoXY(6 + 4 * tx, 3 + 2 * ty);
		coutColored("O", ndcolor);
	}
	if ((pos_i != ty || pos_j != tx) && (pos_i != -1 || pos_j != -1)) {
		common::gotoXY(6 + 4 * pos_j, 3 + 2 * pos_i);
		coutColored("O", ndcolor);
	}
}

int game::game_pve(game& g, int stcolor, int ndcolor) {
	int key = -1;
	clearConsole();
	g.drawBoard(stcolor, ndcolor);
	drawInformation(false, stcolor, ndcolor);
	common::playSound(Start);
	g.showScore();
	int flag = g.win();
	while (!flag && !g.draw()) {
		g.showTurn();
		g.drawCursor();
		key = getInput();
		g.pveMove(key, stcolor, ndcolor);
		if (key == 6) {
			common::playSound(Select);
			clearConsole();
			printRectangle(40, 12, 34, 2);
			printText("Do you want to save? (Y/N)", 45, 13);
			while (false == false) {
				key = getInput();
				if (key == 9) {
					file::saveScreen(g);
					return 0;
				}
				if (key == 10) {
					common::playSound(Select);
					return -1;
				}
			}
		}
		if (key == 7) {
			file::saveScreen(g);
			return 0;
		}
		if (key == 8) {
			file::loadScreen(g);
			return 0;
		}
		flag = g.win();
		if (flag) break;
		g.processBoardPveO(stcolor, ndcolor);
		flag = g.win();
	}
	return flag;
}

void game::processBoardPveX(int stcolor, int ndcolor) {
	if (board[y][x]) return;
	if (x_turn) {
		board[y][x] = 1;
		x_count++;
		x_turn = false;
		drawlogoX(x_turn, setC, 3, stcolor);
		drawlogoO(!x_turn, setC + 29, 3, ndcolor);
	}

}
void game::processBoardPveO(int stcolor, int ndcolor) {
	if (!x_turn) {
		Sleep(200);
		findBestMove();
		board[pos_i][pos_j] = 2;
		common::gotoXY(6 + 4 * pos_j, 3 + 2 * pos_i);
		coutColored("O", 181);
		o_count++;
		x_turn = true;
		drawlogoO(!x_turn, setC + 29, 3, ndcolor);
		drawlogoX(x_turn, setC, 3, stcolor);
	}
}

bool game::checkBorder(int x, int y) {
	return (x >= 0 && x < size&& y >= 0 && y < size);
}
void game::findBestMove() {
	int bestPoint = INT_MIN;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (board[i][j] == 0)
			{
				int point = attackPoint(i, j) + defendPoint(i, j);

				if (bestPoint < point) {
					bestPoint = point;
					pos_i = i;
					pos_j = j;
				}
			}
		}
	}
}

int game::attackPoint(int x, int y) {
	int cX[8] = { 1,0,1,1,-1,0,-1,-1 };
	int cY[8] = { 0,1,1,-1,0,-1,-1,1 };
	int mate[4]{}, enemy[4]{}, block[4]{};
	int sumPoint = 0, point = 0;
	for (int k = 0; k < 8; k++) {
		for (int i = 1; i <= 4; i++) {

			if (!checkBorder(x + i * cX[k], y + i * cY[k])) {
				block[k % 4]++;
				break;
			}

			if (board[x + i * cX[k]][y + i * cY[k]] == 0) break;

			if (board[x + i * cX[k]][y + i * cY[k]] == 2) {
				mate[k % 4]++;
			}

			if (board[x + i * cX[k]][y + i * cY[k]] == 1) {
				enemy[k % 4]++;
				break;
			}
		}
	}

	for (int i = 0; i < 4; i++) {
		point = attackEvaluate[mate[i]];
		if (mate[i] >= 4) point = attackEvaluate[4];
		if (enemy[i] >= 1 || block[i] >= 1) point /= 2;
		if (enemy[i] >= 1 && mate[i] < 4 && block[i] >= 1) point = 0;
		sumPoint += point;
	}

	return sumPoint;
}

int game::defendPoint(int x, int y) {
	int cX[8] = { 1,0,1,1,-1,0,-1,-1 };
	int cY[8] = { 0,1,1,-1,0,-1,-1,1 };
	int mate[4]{}, enemy[4]{}, block[4]{};
	int sumPoint = 0, point = 0;
	for (int k = 0; k < 8; k++) {
		for (int i = 1; i <= 4; i++) {
			if (!checkBorder(x + i * cX[k], y + i * cY[k])) {
				block[k % 4]++;
				break;
			}

			if (board[x + i * cX[k]][y + i * cY[k]] == 0) break;

			if (board[x + i * cX[k]][y + i * cY[k]] == 1) {
				enemy[k % 4]++;
			}

			if (board[x + i * cX[k]][y + i * cY[k]] == 2) {
				mate[k % 4]++;
				break;
			}
		}
	}

	for (int i = 0; i < 4; i++) {
		point = defendEvaluate[enemy[i]];
		if (enemy[i] >= 4) point = defendEvaluate[4];
		if ((mate[i] >= 1) || (block[i] >= 1)) point /= 2;
		if (mate[i] >= 1 && enemy[i] < 4 && block[i] >= 1) point = 0;
		sumPoint += point;
	}

	return sumPoint;
}
void drawlogoX(bool status, int x, int y, int stcolor)
{
	int bgColor, pixColor, halfColor;
	if (status == 1)
	{
		bgColor = Black;
		pixColor = stcolor;
		halfColor = (stcolor - 240) * 16;
	}
	else 
	{
		bgColor = White;
		pixColor = Black;
		halfColor = whiteBlack;
	}
	//black up, red bg
	//2
	drawRowPixel(halfColor, pixelUp, 4, x + 4, y + 1);
	drawRowPixel(halfColor, pixelUp, 4, x + 14, y + 1);
	//3
	drawXY(halfColor, pixelUp, x + 7, y + 2);
	drawXY(halfColor, pixelUp, x + 14, y + 2);
	//4
	drawXY(halfColor, pixelUp, x + 9, y + 3);
	drawXY(halfColor, pixelUp, x + 12, y + 3);
	//5
	drawRowPixel(halfColor, pixelUp, 2, x + 10, y + 4);
	//7
	drawXY(halfColor, pixelUp, x + 6, y + 6);
	drawXY(halfColor, pixelUp, x + 13, y + 6);
	//8
	drawRowPixel(halfColor, pixelUp, 2, x + 5, y + 7);
	drawRowPixel(halfColor, pixelUp, 2, x + 15, y + 7);
	//10
	drawXY(halfColor, pixelUp, x + 1, y + 9);
	drawXY(halfColor, pixelUp, x + 20, y + 9);
	//11
	drawRowPixel(halfColor, pixelUp, 16, x + 3, y + 10);

	//black down, red bg
	//1
	drawRowPixel(halfColor, pixelDown, 16, x + 3, y);
	//2
	drawXY(halfColor, pixelDown, x + 1, y + 1);
	drawXY(halfColor, pixelDown, x + 20, y + 1);
	//4
	drawRowPixel(halfColor, pixelDown, 2, x + 5, y + 3);
	drawRowPixel(halfColor, pixelDown, 2, x + 15, y + 3);
	//7
	drawRowPixel(halfColor, pixelDown, 2, x + 10, y + 6);
	//8
	drawXY(halfColor, pixelDown, x + 9, y + 7);
	drawXY(halfColor, pixelDown, x + 12, y + 7);
	//9
	drawXY(halfColor, pixelDown, x + 7, y + 8);
	drawXY(halfColor, pixelDown, x + 14, y + 8);
	//10
	drawRowPixel(halfColor, pixelDown, 4, x + 4, y + 9);
	drawRowPixel(halfColor, pixelDown, 4, x + 14, y + 9);

	//black
	//2
	drawRowPixel(bgColor, pixel, 2, x + 2, y + 1);
	drawRowPixel(bgColor, pixel, 6, x + 8, y + 1);
	drawRowPixel(bgColor, pixel, 2, x + 18, y + 1);
	//3
	drawRowPixel(bgColor, pixel, 3, x + 1, y + 2);
	drawRowPixel(bgColor, pixel, 6, x + 8, y + 2);
	drawRowPixel(bgColor, pixel, 3, x + 18, y + 2);
	//4
	drawRowPixel(bgColor, pixel, 4, x + 1, y + 3);
	drawRowPixel(bgColor, pixel, 2, x + 10, y + 3);
	drawRowPixel(bgColor, pixel, 4, x + 17, y + 3);
	//5
	drawRowPixel(bgColor, pixel, 6, x + 1, y + 4);
	drawRowPixel(bgColor, pixel, 6, x + 15, y + 4);
	//6
	drawRowPixel(bgColor, pixel, 7, x + 1, y + 5);
	drawRowPixel(bgColor, pixel, 7, x + 14, y + 5);
	//7
	drawRowPixel(bgColor, pixel, 6, x + 1, y + 6);
	drawRowPixel(bgColor, pixel, 6, x + 15, y + 6);
	//8
	drawRowPixel(bgColor, pixel, 4, x + 1, y + 7);
	drawRowPixel(bgColor, pixel, 2, x + 10, y + 7);
	drawRowPixel(bgColor, pixel, 4, x + 17, y + 7);
	//9
	drawRowPixel(bgColor, pixel, 3, x + 1, y + 8);
	drawRowPixel(bgColor, pixel, 6, x + 8, y + 8);
	drawRowPixel(bgColor, pixel, 3, x + 18, y + 8);
	//10
	drawRowPixel(bgColor, pixel, 2, x + 2, y + 9);
	drawRowPixel(bgColor, pixel, 6, x + 8, y + 9);
	drawRowPixel(bgColor, pixel, 2, x + 18, y + 9);

	//white
	//1
	drawXY(White, pixel, x, y);
	drawXY(White, pixel, x + 21, y);
	//11
	drawXY(White, pixel, x, 10);
	drawXY(White, pixel, x + 21, 10);

	//red
	common::setColor(pixColor);
	unsigned char red[] = {
		3,20,0,
		0,
		1,5,6,7,16,17,18,22,0,
		1,8,9,14,15,22,0,
		1,8,9,10,13,14,15,22,0,
		1,9,10,11,12,13,14,22,0,
		1,8,9,10,13,14,15,22,0,
		1,8,9,14,15,22,0,
		1,5,6,7,16,17,18,22,0,
		0,
		3,20,0
	};
	drawSymbolPixel(pixel, red, x, y);
	common::setColor(Black);

	//red down
	//1
	drawXY(pixColor, pixelDown, x + 1, y);
	drawXY(pixColor, pixelDown, x + 20, y);
	//2
	drawXY(pixColor, pixelDown, x, y + 1);
	drawXY(pixColor, pixelDown, x + 21, y + 1);

	//red up
	//10
	drawXY(pixColor, pixelUp, x, y + 9);
	drawXY(pixColor, pixelUp, x + 21, y + 9);
	//11
	drawXY(pixColor, pixelUp, x + 1, y + 10);
	drawXY(pixColor, pixelUp, x + 20, y + 10);
}

void drawlogoO(bool status, int x, int y, int ndcolor)
{
	int bgColor, pixColor, halfColor;
	if (status == 1)
	{
		bgColor = Black;
		pixColor = ndcolor;
		halfColor = (ndcolor - 240) * 16;
	}
	else
	{
		bgColor = White;
		pixColor = Black;
		halfColor = whiteBlack;
	}
	//black down, blue bg
	//1
	drawRowPixel(halfColor, pixelDown, 16, x + 3, y);
	//2
	drawXY(halfColor, pixelDown, x + 1, y + 1);
	drawXY(halfColor, pixelDown, x + 20, y + 1);
	//4
	drawXY(halfColor, pixelDown, x + 7, y + 3);
	drawXY(halfColor, pixelDown, x + 14, y + 3);
	//5
	drawXY(halfColor, pixelDown, x + 6, y + 4);
	drawXY(halfColor, pixelDown, x + 13, y + 4);
	drawXY(halfColor, pixelDown, x + 15, y + 4);
	//9
	drawXY(halfColor, pixelDown, x + 5, y + 8);
	drawXY(halfColor, pixelDown, x + 16, y + 8);
	//10
	drawRowPixel(halfColor, pixelDown, 6, x + 8, y + 9);

	//black up. halfColor bg
	//2
	drawRowPixel(halfColor, pixelUp, 6, x + 8, y + 1);
	//3
	drawXY(halfColor, pixelUp, x + 5, y + 2);
	drawXY(halfColor, pixelUp, x + 16, y + 2);
	//4
	drawRowPixel(halfColor, pixelUp, 3, x + 10, y + 3);
	//7
	drawXY(halfColor, pixelUp, x + 6, y + 6);
	drawXY(halfColor, pixelUp, x + 15, y + 6);
	//8
	drawXY(halfColor, pixelUp, x + 7, y + 7);
	drawXY(halfColor, pixelUp, x + 14, y + 7);
	//10
	drawXY(halfColor, pixelUp, x + 1, y + 9);
	drawXY(halfColor, pixelUp, x + 20, y + 9);
	//11
	drawRowPixel(halfColor, pixelUp, 16, x + 3, y + 10);

	//bgColor
	//2
	drawRowPixel(bgColor, pixel, 6, x + 2, y + 1);
	drawRowPixel(bgColor, pixel, 6, x + 14, y + 1);
	//3
	drawRowPixel(bgColor, pixel, 4, x + 1, y + 2);
	drawRowPixel(bgColor, pixel, 4, x + 17, y + 2);
	//4
	drawRowPixel(bgColor, pixel, 4, x + 1, y + 3);
	drawRowPixel(bgColor, pixel, 2, x + 8, y + 3);
	drawXY(bgColor, pixel, x + 13, y + 3);
	drawRowPixel(bgColor, pixel, 4, x + 17, y + 3);
	//5
	drawRowPixel(bgColor, pixel, 3, x + 1, y + 4);
	drawRowPixel(bgColor, pixel, 6, x + 7, y + 4);
	drawXY(bgColor, pixel, x + 14, y + 4);
	drawRowPixel(bgColor, pixel, 3, x + 18, y + 4);
	//6
	drawRowPixel(bgColor, pixel, 3, x + 1, y + 5);
	drawRowPixel(bgColor, pixel, 10, x + 6, y + 5);
	drawRowPixel(bgColor, pixel, 3, x + 18, y + 5);
	//7
	drawRowPixel(bgColor, pixel, 3, x + 1, y + 6);
	drawRowPixel(bgColor, pixel, 8, x + 7, y + 6);
	drawRowPixel(bgColor, pixel, 3, x + 18, y + 6);
	//8
	drawRowPixel(bgColor, pixel, 4, x + 1, y + 7);
	drawRowPixel(bgColor, pixel, 6, x + 8, y + 7);
	drawRowPixel(bgColor, pixel, 4, x + 17, y + 7);
	//9
	drawRowPixel(bgColor, pixel, 4, x + 1, y + 8);
	drawRowPixel(bgColor, pixel, 4, x + 17, y + 8);
	//10
	drawRowPixel(bgColor, pixel, 6, x + 2, y + 9);
	drawRowPixel(bgColor, pixel, 6, x + 14, y + 9);

	//blue
	common::setColor(pixColor);
	unsigned char blue[] = {
		3,20,0,
		0,
		1,7,8,9,10,11,12,13,14,15,16,22,0,
		1,6,7,16,17,22,0,
		1,5,6,17,18,22,0,
		1,5,6,17,18,22,0,
		1,5,6,17,18,22,0,
		1,6,7,16,17,22,0,
		1,7,8,9,10,11,12,13,14,15,16,22,0,
		0,
		3,20,0
	};
	drawSymbolPixel(pixel, blue, x, y);

	//white
	//1
	drawXY(White, pixel, x, y);
	drawXY(White, pixel, x + 21, y);
	//11
	drawXY(White, pixel, x, y + 10);
	drawXY(White, pixel, x + 21, y + 10);

	//blue up
	//10
	drawXY(pixColor, pixelUp, x, y + 9);
	drawXY(pixColor, pixelUp, x + 21, y + 9);
	//11
	drawXY(pixColor, pixelUp, x + 1, y + 10);
	drawXY(pixColor, pixelUp, x + 20, y + 10);


	//blue down
	//1
	drawXY(pixColor, pixelDown, x + 1, y);
	drawXY(pixColor, pixelDown, x + 20, y);
	//2
	drawXY(pixColor, pixelDown, x, y + 1);
	drawXY(pixColor, pixelDown, x + 21, y + 1);

}


