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
		do {
			g.askContinuePlay(key);
			if (key == 9) {
				g.resetData();
				key = -1;
				break;
			}
			else if (key == 10) {
				system("cls");
				common::setUpConsole();
				system("color F0");
				drawBoard();
				drawInformation();
				common::playSound(Start);
				g.showScore();
				// them ham load vi tri cu
				//
				//
				//
				key = -1;
				break;
			}

		} while (key != 9 && key != 10);
	} while (1);

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
	ifstream pic(loc + name);
	if (!pic) return;
	string line;
	while (getline(pic, line)) {
		common::gotoXY(x, y++);
		coutColored(line, color);
	}
	pic.close();
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
	draw_txt("logoX.txt", setC, 0, Red);
	draw_txt("logoO.txt", setC + 31, 0, Grey);
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
		draw_txt("logoX.txt", setC, 0, Grey);
		draw_txt("logoO.txt", setC + 31, 0, Blue);
		x_turn = false;
	}
	else {
		board[y][x] = 2;
		o_count++;
		draw_txt("logoO.txt", setC + 31, 0, Grey);
		draw_txt("logoX.txt", setC, 0, Red);
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

void game::draw_effect()
{
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
	common::gotoXY(55, 24);
	cout << "Continue?";
	common::gotoXY(38, 25);
	cout << "Press Y to continue, N to see the last board.";
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
	key = getInput();
	//if (i == 6) exit(0);
}

void game::saveGame(string file)
{
	ofstream game(file);
	if (!game) return;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			game << board[i][j] << " ";
		}
		game << endl;
	}
	game << x_score << " " << o_score << endl;
	game << x << " " << y << endl;
	game.close();
}
void game::loadGame(string file) {
	ifstream game(file);
	x_count = o_count = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			game >> board[i][j];
			if (board[i][j] == 1)		x_count++;
			else if (board[i][j] == 2)	o_count++;
		}
	}
	game >> x_score >> o_score;
	game >> x >> y;
	x_turn = (x_count == o_count);
	game.close();
}
int game::minimax(bool isMaxiPlayer, int depth, int alpha, int beta) {
	//int val = 0;
	bool stop = false;
	if (depth == 0) return 0;
	int i = 0, j = 0;
	if (draw()) {
		return 0;
	}
	else if (win()) {
		if (!x_turn) {
			return -10;
		}
		else {
			return 10;
		}
	}
	else {
		//else if (depth == 0) return value;
		if (isMaxiPlayer) {
			int bestVal = -1000;
			for (i = y-5; i < y+5; ++i) {
				for (j = x-5; j < x+5; ++j) {
					if (i >= 0 && i < size && j >= 0 && j <= size) {
						if (board[i][j] == 0) {
							board[i][j] = 1;
							val = minimax(false, depth - 1, alpha, beta);
							board[i][j] = 0;
							bestVal = max(bestVal, val);
							alpha = max(alpha, bestVal);
							if (beta <= alpha) {
								return bestVal;
							}
						}
					}
				}
			}
			return bestVal;
		}
		else {
			int bestVal = 1000;
			for (i = y-5; i < y + 5; ++i) {
				for (j = x-5; j < x + 5; ++j) {
					if (i >= 0 && i < size && j >= 0 && j <= size) {
						if (board[i][j] == 0) {
							board[i][j] = 2;
							val = minimax(true, depth - 1, alpha, beta);
							board[i][j] = 0;
							bestVal = min(bestVal, val);
							beta = min(beta, bestVal);
							if (beta <= alpha) {
								return bestVal;

							}
						}
					}
				}
			}
			return bestVal;
		}
	}
}
void game::findBestMove(bool isMaxiPlayer, int& pos_i, int& pos_j) {
	int bestVal = 1000;
	bool stop = false;
	//minimax(false,depth,-1000, 1000);
	for (int i = y; i <y+5; ++i) {
		for (int j = x; j < x+5; ++j) {
			if (i >= 0 && i < size && j >= 0 && j <= size) {
				if (board[i][j] == 0) {
					board[i][j] = 2;
					int val = minimax(false, depth, -1000, 1000);
					if (val < bestVal) {
						bestVal = val;
						pos_i = i;
						pos_j = j;
					}
					board[i][j] = 0;
					//printf("%d ", i, j);
				}
			}
		}

	}
	printf("%d %d ", pos_i, pos_j);

}
void game::pveMove() {
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
		processBoardPveX();
		//x_turn = false;
		//findMove(false);
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

	//processBoardPveO();

}

void game::game_pve() {

	game g;
	//g.minimax(false);
	int key = -1;
	do {
		system("cls");
		common::setUpConsole();
		system("color F0");
		drawBoard();
		drawInformation();
		common::playSound(Start);
		g.showScore();
		while (!g.draw()) {
			g.showTurn();
			//if (g.x_turn)
			g.pveMove();
			if (g.win()) break;
			//g.findBestMove(false, g.pos_i, g.pos_j);
			g.processBoardPveO();
			if (g.win()) break;


		}
		g.score();
		g.showScore();
		system("cls");
		g.endEffect();
		do {
			g.askContinuePlay(key);
			if (key == 9) {
				g.resetData();
				key = -1;
				break;
			}
			else if (key == 10) {
				system("cls");
				common::setUpConsole();
				system("color F0");
				drawBoard();
				drawInformation();
				common::playSound(Start);
				g.showScore();
				// them ham load vi tri cu
				//
				//
				//
				key = -1;
				break;
			}

		} while (key != 9 && key != 10);
	} while (1);
}

void game::processBoardPveX() {
	if (board[y][x]) return;
	if (x_turn) {
		board[y][x] = 1;
		x_count++;
		draw_txt("logoX.txt", setC, 0, Grey);
		draw_txt("logoO.txt", setC + 31, 0, Blue);
		x_turn = false;
	}

}
void game::processBoardPveO() {
	if (!x_turn) {
		findBestMove(false, pos_j, pos_i);
		x = pos_i;
		y = pos_j;
		board[y][x] = 2;
		//board[pos_i][pos_j] = 2;
		common::gotoXY(6 + 4 * pos_i, 3 + 2 * pos_j);
		coutColored("O", DarkBlue);
		o_count++;
		Sleep(100);
		draw_txt("logoO.txt", setC + 31, 0, Grey);
		draw_txt("logoX.txt", setC, 0, Red);
		x_turn = true;
	}
}
