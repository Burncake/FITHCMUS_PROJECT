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
	for (int m = 0; m < size; m++) {
		for (int n = 0; n < size; n++) {
			for (int i = -4; i < 5; i++) {
				if (!board[m][n]) {
					countR = 0, countD = 0, countUR = 0, countDR = 0;
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
				if ((countR == 5) || (countD == 5) || (countDR == 5) || (countUR == 5)) return true;
			}
		}
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


int game::minimax(bool ismaxiPlayer, int depth, int alpha, int beta) {
	const int HUMAN_PLAYER = 1;
	const int AI_PLAYER = 2;

	//int c = depth * 1000;
	if (win()||depth==0) {
		return evaluate();
	}

	if (ismaxiPlayer) {
		int bestScore = INT_MIN;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (board[i][j] == 0) {
					board[i][j] = HUMAN_PLAYER;
					int score = minimax(false, depth - 1, alpha, beta);
					board[i][j] = 0;
					bestScore = max(bestScore, score);
					alpha = max(alpha, bestScore);
					if (beta <= alpha) {
						break;
					}
				}
			}
		}
		return bestScore;
	}
	else {
		int bestScore = INT_MAX;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (board[i][j] == 0) {
					board[i][j] = AI_PLAYER;
					int score = minimax(true, depth - 1, alpha, beta);
					board[i][j] = 0;
					bestScore = min(bestScore, score);
					beta = min(beta, bestScore);
					if (beta <= alpha) {
						break;
					}
				}
			}
		}
		return bestScore;
	}
}

void game::findBestMove( int& pos_i, int& pos_j) {
	int bestVal = INT_MIN;
	bool stop = false;
	for (int i = 0; i < size ; ++i) {
		for (int j = 0; j < size ; ++j) {
			if (board[i][j] == 0) {
				board[i][j] = 2;
				int val = minimax(false,2, INT_MIN, INT_MAX);
				board[i][j] = 0;

				if (val > bestVal) {
					bestVal = val;
					pos_i = i;
					pos_j = j;
				}

				
			}
		}
	}
	cout << pos_i << pos_j;

	return;
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
	//		g.board[g.pos_i][g.pos_j] = 2;
			g.pveMove();
			if(g.win()) break;
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
		findBestMove(pos_i,pos_j);
		board[pos_i][pos_j] = 2;
		/*x = pos_j;
		y = pos_i;*/
		common::gotoXY(6 + 4 * pos_j, 3 + 2 * pos_i);

		coutColored("O", DarkBlue);
		o_count++;
		Sleep(100);
		draw_txt("logoO.txt", setC + 31, 0, Grey);
		draw_txt("logoX.txt", setC, 0, Red);
		Sleep(100);
		x_turn = true;
	}
}
int game::evaluate() {
	int maxiPlayerScore = 0;
	bool check3Min = false;
	bool check3Max = false;
	int miniPlayerScore = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (board[i][j] == 2) {
				if (checkWinScore(i, j, 2)) return INT_MAX;
				maxiPlayerScore += evaluateCell(i, j, 2);
			}
			else if (board[i][j] == 1) {
				if (checkWinScore(i, j, 1)) return INT_MIN;

				miniPlayerScore += evaluateCell(i, j, 1);
			}
		}
	}
	/*if (check3Max) return INT_MIN;
	if(check3Min) return INT_MAX;
	*/
	return maxiPlayerScore - miniPlayerScore;
}


int game::evaluateCell(int row, int col, int move) {
	int score = 0;
	//check horizontal
	int count = 0;
	for (int i = col; i >= 0; i--) {
		if (board[row][i] == move) {
			count++;
		}
		else if (board[row][i] == 0) {
			break;
		}
		else {
			count = 0;
			break;
		}
	}
	for (int i = col + 1; i < 12; i++) {
		if (board[row][i] == move) {
			count++;
		}
		else if (board[row][i] == 0) {
			break;
		}
		else {
			count = 0;
			break;
		}
	}
	if (count == 1) {
		score += 1;
	}
	else if (count == 2) {
		score += 10;
	}
	else if (count == 3) {
		score += 100;
	}
	else if (count == 4) {
		score += 1000;
	}
	else if (count == 5) {
		score += 10000;
	}

	//check vertical
	count = 0;
	for (int i = row; i >= 0; i--) {
		if (board[i][col] == move) {
			count++;
		}
		else if (board[i][col] == 0) {
			break;
		}
		else {
			count = 0;

			break;
		}
	}
	for (int i = row + 1; i < 12; i++) {
		if (board[i][col] == move) {
			count++;
		}
		else if (board[i][col] == 0) {
			break;
		}
		else {
			count = 0;

			break;
		}
	}
	if (count == 1) {
		score += 1;
	}
	else if (count == 2) {
		score += 10;
	}
	else if (count == 3) {
		score += 100;
	}
	else if (count == 4) {
		score += 1000;
	}
	else if (count == 5) {
		score += 10000;
	}
	
	//check diagonal
	count = 0;

	for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
		if (board[i][j] == move) {
			count++;
		}
		else if (board[i][j] == 0) {
			break;
		}
		else {
			count = 0; 

			break;
		}
	}
	for (int i = row + 1, j = col + 1; i < 12 && j < 12; i++, j++) {
		if (board[i][j] == move) {
			count++;
		}
		else if (board[i][j] == 0) {
			break;
		}
		else {
			count = 0;

			break;
		}
	}
	if (count == 1) {
		score += 1;
	}
	else if (count == 2) {
		score += 10;
	}
	else if (count == 3) {
		score += 100;
	}
	else if (count == 4) {
		score += 1000;
	}
	else if (count == 5) {
		score += 10000;
	}

	//check anti-diagonal
	count = 0;
	for (int i = row, j = col; i >= 0 && j < 12; i--, j++) {
		if (board[i][j] == move) {
			count++;
		}
		else if (board[i][j] == 0) {
			break;
		}
		else {
			count = 0;

			break;
		}
	}
	for (int i = row + 1, j = col - 1; i < 12 && j >= 0; i++, j--) {
		if (board[i][j] == move) {
			count++;
		}
		else if (board[i][j] == 0) {
			break;
		}
		else {
			count = 0;

			break;
		}
	}
	if (count == 1) {
		score += 1;
	}
	else if (count == 2) {
		score += 10;
	}
	else if (count == 3) {
		score += 100;
	}
	else if (count == 4) {
		score += 1000;
	}
	else if (count == 5) {
		score += 10000;
	}
	return score;
}
bool game::checkWinScore(int row, int col, int move) {
	int count = 0;
	for (int i = 1; i <= 4; i++) {
		if (row + i >= size || board[row + i][col] != move) {
			break;
		}
		count++;
	}
	if (count ==4) {
		return true;
	}

	count = 0;
	for (int i = 1; i <= 4; i++) {
		if (col + i >= size || board[row][col + i] != move) {
			break;
		}
		count++;
	}
	if (count ==4) {
		return true;
	}

	count = 0;
	for (int i = 1; i <=4; i++) {
		if (row + i >= size || col + i >= size || board[row + i][col + i] != move) {
			break;
		}
		count++;
	}
	if (count ==4) {
		return true;
	}

	count = 0;
	for (int i = 1; i <= 4; i++) {
		if (row - i < 0 || col + i >= size || board[row - i][col + i] != move) {
			break;
		}
		count++;
	}
	if (count ==4) {
		return true;
	}

	return false;
}