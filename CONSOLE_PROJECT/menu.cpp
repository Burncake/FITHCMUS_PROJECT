#include "menu.h"

//cac lua chon trong menu
string options[6] = { "PLAY GAME", "LOAD GAME", "ABOUT", "HELP", "SETTING", "EXIT" };
//cac che do choi
string gameMode[2] = { "PvP","PvC" };

//man hinh chinh
void menu::mainScreen(int selectedMenu) {
	int x = 51, y = 14;
	int flag = selectedMenu;
	common::setColor(Black);
	menu::printOptionsBoard();
	common::setColor(Black);
	
	if (flag == 0) common::setColor(Red);
	printText(options[0], x + 1, y);
	common::setColor(Black);
	if (flag == 1) common::setColor(Red);
	printText(options[1], x + 1, y + 2);
	common::setColor(Black);
	if (flag == 2) common::setColor(Red);
	printText(options[2], x + 3, y + 4);
	common::setColor(Black);
	if (flag == 3) {
		common::setColor(Red);
		printText(" " + options[3], x + 3, y + 6);
	}
	else printText(options[3] + " ", x + 3, y + 6);
	common::setColor(Black);
	if (flag == 4) common::setColor(Red);
	printText(options[4], x + 2, y + 8);
	common::setColor(Black);
	if (flag == 5) {
		common::setColor(Red);
		printText(" " + options[5], x + 3, y + 10);
	}
	else printText(options[5] + " ", x + 3, y + 10);
}

void menu::settingScreen(int selectedMenu, int& x, int& y, const int cursor, menu& m) {
	int flag = selectedMenu;
	common::setColor(Black);
	printRectangle(x - 2, y - 1, 45, 6);
	printText("================= SETTING =================", x, y);
	printText("Press ESC to go back", 48, 28);

	if (flag == 0) {
		printText(" ", cursor - 2, y + 3);
		printText(" ", cursor - 2, y + 4);
		common::setColor(Red);
		printText(">", cursor - 2, y + 2);
	}
	printText("Background Music:", x, y + 2);
	common::setColor(Black);
	if (m.music) printText("On ", cursor, y + 2);
	else printText("Off", cursor, y + 2);
	if (flag == 1) {
		printText(" ", cursor - 2, y + 4);
		printText(" ", cursor - 2, y + 2);
		common::setColor(Red);
		printText(">", cursor - 2, y + 3);
	}
	printText("First player color:", x, y + 3);
	common::setColor(m.color[m.st_color]);
	switch (m.st_color) {
	case 0:
		printText("Red   ", cursor, y + 3);
		break;
	case 1:
		printText("Blue  ", cursor, y + 3);
		break;
	case 2:
		printText("Cyan  ", cursor, y + 3);
		break;
	case 3:
		printText("Aqua  ", cursor, y + 3);
		break;
	case 4:
		printText("Green ", cursor, y + 3);
		break;
	case 5:
		printText("Pink  ", cursor, y + 3);
		break;
	case 6:
		printText("Purple", cursor, y + 3);
		break;
	}
	common::setColor(Black);
	if (flag == 2) {
		printText(" ", cursor - 2, y + 2);
		printText(" ", cursor - 2, y + 3);
		common::setColor(Red);
		printText(">", cursor - 2, y + 4);
	}
	printText("Second player | BOT color:", x, y + 4);
	common::setColor(m.color[m.nd_color]);
	switch (m.nd_color) {
	case 0:
		printText("Red   ", cursor, y + 4);
		break;
	case 1:
		printText("Blue  ", cursor, y + 4);
		break;
	case 2:
		printText("Cyan ", cursor, y + 4);
		break;
	case 3:
		printText("Aqua  ", cursor, y + 4);
		break;
	case 4:
		printText("Green  ", cursor, y + 4);
		break;
	case 5:
		printText("Pink  ", cursor, y + 4);
		break;
	case 6:
		printText("Purple", cursor, y + 4);
		break;
	}
	common::setColor(Black);
}

void menu::modeSelection(menu& m) {
	int selectedMode = 0;
	while (false == false) {
		menu::drawGameMode(selectedMode);
		int a = getInput();
		common::playSound(Move);
		if (a == 1) selectedMode = (selectedMode - 1 + 2) % 2;
		if (a == 3) selectedMode = (selectedMode + 1) % 2;
		if (a == 5) {
			common::playSound(Select);
			break;
		}
		if (a == 6) return;
	}

	game g;
	if (selectedMode) {
		g.mode = pve;
		game::game_pve(g, m.color[m.st_color], m.color[m.nd_color]);
	}
	else {
		g.mode = pvp;
		game::game_pvp(g, m.color[m.st_color], m.color[m.nd_color]);
	}
}

void menu::menuSelection(menu& m) {
	clearConsole();
	int selectedMenu = 0;

	printLogo();
	bigOScreen();
	bigXScreen();
	particles();
	
	while (false == false) {
		menu::mainScreen(selectedMenu);
		int a = getInput();
		common::playSound(Move);
		if (a == 1) selectedMenu = (selectedMenu - 1 + 6) % 6;
		if (a == 3) selectedMenu = (selectedMenu + 1) % 6;
		if (a == 5) {
			common::playSound(Select);
			break;
		}
	}

	switch (selectedMenu) {
		case 0: {
			clearConsole();
			menu::modeSelection(m);
			return;
		}
		case 1: {
			game g;
			if (file::loadScreen(g)) {
				if (g.mode == pvp) game::game_pvp(g, m.color[m.st_color], m.color[m.nd_color]);
				if (g.mode == pve) game::game_pve(g, m.color[m.st_color], m.color[m.nd_color]);
			}
			return;
		}
		case 2: {
			clearConsole();
			menu::aboutScreen();
			while (getInput() != 6);
			return;
		}
		case 3: {
			clearConsole();
			menu::helpScreen();
			while (getInput() != 6);
			return;
		}
		case 4: {
			clearConsole();
			menu::setting(m);
			return;
		}
		case 5: {
			clearConsole();
			menu::exitSelection(m);
			return;
		}
		default: return;
	}
}

//ve cac che do cua game
void menu::drawGameMode(int selectedMode) {
	//menu::clearConsole();
	int x = 52, y = 15;
	int flag = selectedMode;
	printLogo();
	common::setColor(Black);
	menu::printModeBoard();
	common::setColor(Black);
	if (flag == 0) common::setColor(Red);
	printText(gameMode[0], x + 4, y);
	common::setColor(Black);
	if (flag == 1) common::setColor(Red);
	printText(gameMode[1], x + 4, y + 2);
	common::setColor(Black);
	printText("Press ESC to go back", 48, 28);	
}

//ve bang cac che do game
void menu::printModeBoard() {
	common::setColor(Black);
	int left = 51;
	int top = 14;

	common::gotoXY(left, top);
	putchar(201);
	for (int i = 1; i < 12; i++) putchar(205);
	putchar(187);

	for (int i = 1; i < 4; i++) {
		common::gotoXY(left, top + i);
		if (i % 2 != 0) {
			putchar(186);
			common::gotoXY(left + 12, top + i);
			putchar(186);
		}
		else {
			putchar(199);
			for (int i = 1; i < 12; i++) putchar(196);
			putchar(182);
		}
	}

	common::gotoXY(left, top + 4);
	putchar(200);
	for (int i = 1; i < 12; i++) putchar(205);
	putchar(188);
}

//void menu::printOptionsBoard() {
//	common::setColor(Black);
//	int left = 50;
//	int top = 13;
//	common::gotoXY(left, top);
//	putchar(201);
//	for (int i = 1; i < 12; i++)
//	{
//		putchar(205);
//	}
//	putchar(187);
//
//
//	for (int i = 1; i < 12; i++)
//	{
//		common::gotoXY(left, top + i);
//		if (i % 2 != 0)
//		{
//			putchar(186);
//			common::gotoXY(left + 12, top + i);
//			putchar(186);
//		}
//		else
//		{
//			putchar(199);
//			for (int i = 1; i < 12; i++)
//			{
//				putchar(196);
//			}
//			putchar(182);
//		}
//	}
//	common::gotoXY(left, top + 12);
//	putchar(200);
//	for (int i = 1; i < 12; i++)
//	{
//		putchar(205);
//	}
//	putchar(188);
//}

void menu::printOptionsBoard() {
	common::setColor(Black);
	int left = 50;
	int top = 13;
	common::gotoXY(left, top);
	putchar(219);
	for (int i = 1; i < 12; i++) putchar(223);
	putchar(219);

	for (int i = 1; i < 12; i++) {
		common::gotoXY(left, top + i);
		if (i % 2 != 0) {
			putchar(219);
			common::gotoXY(left + 12, top + i);
			putchar(219);
		}
		else {
			putchar(199);
			for (int i = 1; i < 12; i++) putchar(196);
			putchar(182);
		}
	}

	common::gotoXY(left, top + 12);
	putchar(219);

	for (int i = 1; i < 12; i++) putchar(220);
	putchar(219);
}

void menu::saveSetting(menu m)
{
	string location = loc;
	ofstream out(location + m_manager);
	if (!out) {
		out.close();
		return;
	}
	if (m.music) out << 1 << endl;
	else out << 0 << endl;
	out << m.st_color << " " << m.nd_color;
	out.close();
}

//Luat choi
void menu::helpScreen() {
	common::setColor(DarkCyan);
	printLogo();

	int x = 15;
	int y = 12;
	int left = 14, top = 11, width = 86, height = 14;
	common::setColor(Black);
	printRectangle(left, top, width, height);
	printText(" ==================================== HUONG DAN =====================================", x, y);
	printText(" 'W' | ' ' : Di chuyen len tren \t\t 'S' | ' ' : Di chuyen xuong duoi", x + 3, y + 1);
	printText(" 'A' | ' ' : Di chuyen sang trai\t\t 'D' | ' ' : Di chuyen sang phai ", x + 3, y + 2);
	common::gotoXY(x + 11, y + 1);
	putchar(30);
	common::gotoXY(x + 57, y + 1);
	putchar(31);
	common::gotoXY(x + 11, y + 2);
	putchar(17);
	common::gotoXY(x + 57, y + 2);
	putchar(16);
	printText(" ==================================== LUAT CHOI =====================================", x, y + 5);
	printText(" - Hai nguoi choi lan luot di chuyen va chon vao cac o chua duoc danh. ", x, y + 6);
	printText(" - Nguoi choi se chien thang tro choi khi nguoi choi do co 5 quan co lien tiep nhau", x, y + 7);
	printText(" theo hang ngang, hang doc hoac hang cheo.", x, y + 8);
	printText(" - Khi tat ca cac o tren ban co deu kin ma chua ai chien thang thi game dau hoa nhau.", x, y + 9);
	printText("Chuc cac ban choi game vui ve!", width / 2, y + 11);
	printText("Press ESC to go back", 48, 28);
}

//Thong tin nhom
void menu::aboutScreen() {
	common::setColor(DarkCyan);
	printLogo();

	int x = 37, y = 14;
	int left = 36, top = 12, width = 42, height = 14;
	common::setColor(Black);
	printRectangle(left, top, width, height);
	printText("ABOUT", x + 18, y - 2);
	printText(" ============== DO AN CARO ============== ", x, y);
	printText("  TRUONG DAI HOC KHOA HOC TU NHIEN", x + 3, y + 1);
	printText(" ========== GIAO VIEN HUONG DAN ========= ", x, y + 3);
	printText(" THAY TRUONG TOAN THINH", x + 9, y + 4);
	printText(" =========== NHOM 3 - 22CLC01 =========== ", x, y + 6);
	printText("22127141 - NGO HOANG NAM HUNG", x + 7, y + 7);
	printText("22127234 - CAO HOANG LOC", x + 7, y + 8);
	printText("22127418 - NGUYEN KHANH TOAN", x + 7, y + 9);
	printText("22127422 - LE THANH MINH TRI", x + 7, y + 10);
	printText("Press ESC to go back", 48, 28);
}

void menu::setting(menu& m) {
	int selectedMenu = 0;
	int x = 36, y = 14;
	const int cursor_col = 73;
	int a;
	common::showCursor(false);
	printLogo();
	while (false == false) {
		if (m.st_color == m.nd_color) printText("But why?", cursor_col, y + 6);
		else printText("        ", cursor_col, y + 6);

		while (false == false) {
			menu::settingScreen(selectedMenu, x, y, cursor_col, m);
			a = getInput();
			common::playSound(Move);
			if (a == 1) selectedMenu = (selectedMenu - 1 + 3) % 3;
			if (a == 3) selectedMenu = (selectedMenu + 1) % 3;
			if (a == 2 || a == 4 || a == 5) {
				common::playSound(Select);
				break;
			}
			if (a == 6) return;
		}

		switch (selectedMenu) {
			case 0:
				if (m.music) m.music = false;
				else m.music = true;
				common::bgmusic(m.music);
				break;
			case 1:
				if (a == 2) m.st_color--;
				if (a == 4 || a == 5) m.st_color++;
				if (m.st_color == -1) m.st_color = 6;
				if (m.st_color == 7) m.st_color = 0;
				break;
			case 2:
				if (a == 2) m.nd_color--;
				if (a == 4 || a == 5) m.nd_color++;
				if (m.nd_color == -1) m.nd_color = 6;
				if (m.nd_color == 7) m.nd_color = 0;
				break;
			default: 
				break;
		}
	}
}

void menu::exitScreen(int selectedOption, int& x, int& y) {
	common::setColor(DarkCyan);
	printLogo();

	int flag = selectedOption;
	common::setColor(Black);
	printRectangle(x - 2, y - 1, 42, 4);
	printText("Are you sure you want to leave the game?", x, y);
	if (flag == 0) common::setColor(79);
	printText("  Yes!  ", x + 7, y + 2);
	common::setColor(Black);
	if (flag == 1) common::setColor(47);
	printText("  No~~  ", x + 25, y + 2);
	common::setColor(Black);
}

void menu::exitSelection(menu m) {
	int selectedOption = 0;
	int x = 38, y = 16;

	while (false == false) {
		menu::exitScreen(selectedOption, x, y);
		int a = getInput();
		common::playSound(Move);
		if (a == 2) selectedOption = (selectedOption - 1 + 2) % 2;
		if (a == 4) selectedOption = (selectedOption + 1) % 2;
		if (a == 5) {
			common::playSound(Select);
			break;
		}
	}

	if (!selectedOption) {
		clearConsole();
		menu::saveSetting(m);
		exit(0);
	}
}

void printCharacter(wstring character, COORD point, int text_color, int background_color) {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD Written;

	int color = (int)text_color + (int)background_color * 16;
	for (int i = 0; i < character.length(); i++) {
		FillConsoleOutputAttribute(hOut, color, 1, point, &Written);
		FillConsoleOutputCharacterW(hOut, character[i], 1, point, &Written);
		point.X++;
	}

}

void startMenu()
{
	common::setUpConsole();
	menu m;
	common::bgmusic(m.music);
	while (false == false) menu::menuSelection(m);
}
