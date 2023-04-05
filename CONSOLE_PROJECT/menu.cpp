#include "menu.h"

//cac lua chon trong menu
string options[6] = { "PLAY GAME", "LOAD GAME", "ABOUT", "HELP", "SETTING", "EXIT" };
//cac che do choi
string gameMode[] = { "PvP","PvC" };
//man hinh chinh
void menu::mainScreen(int selectedMenu) {
	int x = 51, y = 14;
	int flag = selectedMenu;
	common::setUpConsole();
	common::setColor(DarkCyan);
	menu::printLogo();
	common::setColor(Black);
	menu::printOptionsBoard();
	common::setColor(Black);
	
	if (flag == 0) {
		common::setColor(Red);
	}
	printText(options[0], x + 1, y);
	common::setColor(Black);
	if (flag == 1) {
		common::setColor(Red);
	}
	printText(options[1], x + 1, y + 2);
	common::setColor(Black);
	if (flag == 2) {
		common::setColor(Red);
	}
	printText(options[2], x + 3, y + 4);
	common::setColor(Black);
	if (flag == 3) {
		common::setColor(Red);
	}
	printText(options[3], x + 3, y + 6);
	common::setColor(Black);
	if (flag == 4) {
		common::setColor(Red);
	}
	printText(options[4], x + 2, y + 8);
	common::setColor(Black);
	if (flag == 5) {
		common::setColor(Red);
	}
	printText(options[5], x + 3, y + 10);
}

void menu::settingScreen(int selectedMenu, int& x, int& y, const int cursor) {
	int flag = selectedMenu;
	common::setColor(DarkCyan);
	menu::printLogo();
	common::setColor(Black);
	menu::printRectangle(x - 2, y - 1, 45, 6);
	printText("================= SETTING =================", x, y);
	printText("Press ESC to go back", 48, 28);

	if (flag == 0) {
		printText(" ", cursor - 2, y + 3);
		printText(" ", cursor - 2, y + 4);
		common::setColor(Red);
		printText(">", cursor - 2, y + 2);
	}
	printText("Background Music:", x, y + 2);
	printText("ON", cursor, y + 2);
	common::setColor(Black);
	if (flag == 1) {
		printText(" ", cursor - 2, y + 4);
		printText(" ", cursor - 2, y + 2);
		common::setColor(Red);
		printText(">", cursor - 2, y + 3);
	}
	printText("First player color:", x, y + 3);
	common::setColor(DarkRed);
	printText("Red", cursor, y + 3);
	common::setColor(Black);
	if (flag == 2) {
		printText(" ", cursor - 2, y + 2);
		printText(" ", cursor - 2, y + 3);
		common::setColor(Red);
		printText(">", cursor - 2, y + 4);
	}
	printText("Second player | BOT color:", x, y + 4);
	common::setColor(DarkBlue);
	printText("Blue", cursor, y + 4);
	common::setColor(Black);
}

void menu::modeSelection() {
	int selectedMode = 0;
	common::showCursor(false);
	while (1) {
		menu::drawGameMode(selectedMode);
		int a = getInput();
		common::playSound(Move);
		if (a == 1) {
			selectedMode = (selectedMode - 1 + 2) % 2;
		}
		else if (a == 3) {
			selectedMode = (selectedMode + 1) % 2;
		}
		else if (a == 5) {
			common::playSound(Select);
			break;
		}
		if (a == 6) {
			menu::clearConsole();
			menuSelection();
			break;
		}

	}
	switch (selectedMode) {
	case 0: {
		game::game_pvp();
		break;
	}
	case 1: {
		game::game_pve();
		break;
	}
	}
}

void menu::menuSelection() {
	common::playSound(Background);
	int selectedMenu = 0;
	
	common::showCursor(false);
	while (1) {
		menu::mainScreen(selectedMenu);
		int a = getInput();
		common::playSound(Move);
		if (a == 1) {
			selectedMenu = (selectedMenu - 1 + 6) % 6;
		}
		else if (a == 3) {
			selectedMenu = (selectedMenu + 1) % 6;
		}
		else if (a == 5) {
			common::playSound(Select);
			break;
		}

	}
	switch (selectedMenu) {
	case 0: {
		menu::clearConsole();
		menu::modeSelection();

		break;
	}
	case 1: {
		menu::clearConsole();
		//ham load file o day
		int c = -1;
		while (c != 6) {
			c = getInput();
			if (c == 6) {
				menu::clearConsole();
				menuSelection();
				break;
			}
		}

		break;
	}
	case 2: {
		menu::clearConsole();
		menu::aboutScreen();
		int c = -1;
		while (c != 6) {
			c = getInput();
			if (c == 6) {
				menu::clearConsole();
				menuSelection();
				break;
			}
		}
		
		break;
	}
	case 3: {
		menu::clearConsole();
		menu::helpScreen();
		int c = -1;
		while (c != 6) {
			c = getInput();
			if (c == 6) {
				menu::clearConsole();
				menuSelection();
				break;
			}
		}

		break;
	}
	case 4: {
		menu::clearConsole();
		menu::setting();
		int c = -1;
		while (c != 6) {
			c = getInput();
			if (c == 6) {
				menu::clearConsole();
				menuSelection();
				break;
			}
		}

		break;
	}
	case 5: {
		menu::clearConsole();
		menu::exitSelection();
		int c = -1;
		while (c != 6) {
			c = getInput();
			if (c == 6) {
				menu::clearConsole();
				menuSelection();
				break;
			}
		}

		break;
	}
	default: break;
	}
}

//ve cac che do cua game
void menu::drawGameMode(int selectedMode) {
	//menu::clearConsole();
	int x = 51, y = 15;
	int flag = selectedMode;
	common::setColor(DarkCyan);
	menu::printLogo();
	common::setColor(Black);
	menu::printModeBoard();
	common::setColor(Black);
	if (flag == 0) {
		common::setColor(Red);
	}
	printText(gameMode[0], x + 4, y);
	common::setColor(Black);
	if (flag == 1) {
		common::setColor(Red);
	}
	printText(gameMode[1], x + 4, y + 2);
	common::setColor(Black);
	printText("Press ESC to go back", 48, 28);	
}

//ve bang cac che do game
void menu::printModeBoard() {
	common::setColor(Black);
	int left = 50;
	int top = 14;
	common::gotoXY(left, top);
	putchar(201);
	for (int i = 1; i < 12; i++)
	{
		putchar(205);
	}
	putchar(187);


	for (int i = 1; i < 4; i++)
	{
		common::gotoXY(left, top + i);
		if (i % 2 != 0)
		{
			putchar(186);
			common::gotoXY(left + 12, top + i);
			putchar(186);
		}
		else
		{
			putchar(199);
			for (int i = 1; i < 12; i++)
			{
				putchar(196);
			}
			putchar(182);
		}
	}
	common::gotoXY(left, top + 4);
	putchar(200);
	for (int i = 1; i < 12; i++)
	{
		putchar(205);
	}
	putchar(188);
}
//logo caro
void menu::printLogo() {
	int width = 114, height = 29;
	unsigned char logo[] = {
		32,32,32,32,220,219,219,219,219,219,219,220,32,32,32,32,32,32,32,220,219,219,220,32,32,32,32,32,254,219,219,219,219,219,219,219,219,220,32,32,32,32,32,220,219,219,219,219,219,219,220,32,
	32,32,220,223,219,32,32,32,32,32,222,219,219,32,32,220,32,220,219,219,32,32,219,219,220,32,32,32,32,219,219,32,221,32,32,32,220,219,219,32,254,32,219,219,223,32,32,32,32,223,219,219,
	32,32,32,219,219,254,32,32,32,32,32,32,32,32,32,32,219,219,223,32,32,32,32,223,219,221,32,32,223,219,219,221,32,32,220,219,219,32,32,32,32,220,223,219,32,32,32,32,32,223,219,219,
	32,223,32,219,219,32,32,32,32,32,32,32,32,32,220,220,223,223,219,219,219,219,219,219,219,219,32,223,32,219,219,219,222,219,219,32,32,32,32,32,32,32,219,219,32,32,32,220,220,32,222,219,
	220,220,32,219,220,223,32,32,32,32,32,219,219,32,32,32,219,219,32,32,32,32,32,220,223,219,223,223,220,223,219,32,32,32,223,219,219,220,32,32,223,221,219,219,220,32,32,32,32,220,219,219,
	32,32,32,32,223,219,219,219,219,219,219,223,32,223,32,222,219,221,32,32,32,32,32,32,219,219,32,32,32,219,219,32,32,32,32,32,254,219,219,32,32,32,32,223,219,219,219,219,219,219,223,32 };
	int num_lines = 6, num_chars = 52;
	int top = 4, left = width / 2 - num_chars / 2;
	for (int i = 0; i < num_lines; i++)
	{
		common::gotoXY(left, i + top);
		for (int j = 0; j < num_chars; j++)
			putchar(logo[i * num_chars + j]);
	}
}

void menu::printOptionsBoard() {
	common::setColor(Black);
	int left = 50;
	int top = 13;
	common::gotoXY(left, top);
	putchar(201);
	for (int i = 1; i < 12; i++)
	{
		putchar(205);
	}
	putchar(187);


	for (int i = 1; i < 12; i++)
	{
		common::gotoXY(left, top + i);
		if (i % 2 != 0)
		{
			putchar(186);
			common::gotoXY(left + 12, top + i);
			putchar(186);
		}
		else
		{
			putchar(199);
			for (int i = 1; i < 12; i++)
			{
				putchar(196);
			}
			putchar(182);
		}
	}
	common::gotoXY(left, top + 12);
	putchar(200);
	for (int i = 1; i < 12; i++)
	{
		putchar(205);
	}
	putchar(188);
}

//Luat choi
void menu::helpScreen() {
	common::setColor(DarkCyan);
	menu::printLogo();

	int x = 15;
	int y = 12;
	int left = 14, top = 11, width = 86, height = 14;
	common::setColor(Black);
	menu::printRectangle(left, top, width, height);
	printText(" ==================================== HUONG DAN =====================================", x, y);
	printText(" 'W' : di chuyen len tren \t\t\t 'S' : di chuyen xuong duoi", x + 6, ++y);
	printText(" 'A' : di chuyen sang trai\t\t\t 'D' : di chuyen sang phai ", x + 6, ++y);
	++y;
	++y;
	printText(" ==================================== LUAT CHOI =====================================", x, ++y);
	printText(" - Hai nguoi choi lan luot di chuyen va chon vao cac o chua duoc danh. ", x, ++y);
	printText(" - Nguoi choi se chien thang tro choi khi nguoi choi do co 5 quan co lien tiep nhau", x, ++y);
	printText(" theo hang ngang, hang doc hoac hang cheo.", x, ++y);
	printText(" - Khi tat ca cac o tren ban co deu kin ma chua ai chien thang thi game dau hoa nhau.", x, ++y); 
	++y;
	++y;
	printText("Chuc cac ban choi game vui ve!", width / 2, y);
	printText("Press ESC to go back", 48, 28);
}

//Thong tin nhom
void menu::aboutScreen() {
	common::setColor(DarkCyan);
	menu::printLogo();

	int x = 36, y = 14;
	int left = 35, top = 12, width = 42, height = 14;
	common::setColor(Black);
	menu::printRectangle(left, top, width, height);
	printText("ABOUT", x + 18, y - 2);
	printText(" ============== DO AN CARO ============== ", x, y);
	printText("  TRUONG DAI HOC KHOA HOC TU NHIEN", x + 3, y + 1);
	printText(" ========== GIAO VIEN HUONG DAN ========= ", x, y + 4);
	printText(" THAY TRUONG TOAN THINH", x + 9, y + 5);
	printText(" =========== NHOM 3 - 22CLC01 =========== ", x, y + 7);
	printText("22127141 - NGO HOANG NAM HUNG", x + 7, y + 8);
	printText("22127234 - CAO HOANG LOC", x + 7, y + 9);
	printText("22127418 - NGUYEN KHANH TOAN", x + 7, y + 10);
	printText("22127422 - LE THANH MINH TRI", x + 7, y + 11);
	printText("Press ESC to go back", 48, 24);
}

void menu::setting() {
	int selectedMenu = 0;
	int x = 36, y = 14;
	const int cursor_col = 75;
	common::showCursor(false);
	while (1) {
		menu::settingScreen(selectedMenu, x, y, cursor_col);
		int a = getInput();
		common::playSound(Move);
		if (a == 1) {
			selectedMenu = (selectedMenu - 1 + 3) % 3;
		}
		else if (a == 3) {
			selectedMenu = (selectedMenu + 1) % 3;
		}
		else if (a == 5) {
			common::playSound(Select);
			break;
		}
		else if (a == 6) {
			menu::clearConsole();
			menuSelection();
			break;
		}
	}

	switch (selectedMenu) {
	case 0: {
		//tat nhac (hoan thien bgmusic khong bi ngat)
		common::gotoXY(cursor_col, y + 2);
		bool backgroundMusic = 1;
		backgroundMusic = !backgroundMusic;
		if (backgroundMusic) {
			cout << "On";
			common::playSound(Background);
		}
		else
			cout << "Off";
		break;
	}
	case 1: {
		//doi mau nhan vat 1
		break;
	}
	case 2: {
		//doi mau nhan vat 2
		break;
	}
	default: break;
	}
}

void menu::exitScreen(int selectedOption, int& x, int& y) {
	common::setColor(DarkCyan);
	menu::printLogo();

	int flag = selectedOption;
	common::setColor(Black);
	menu::printRectangle(x - 2, y - 1, 42, 4);
	printText("Are you sure you want to leave the game?", x, y);
	if (flag == 0) {
		common::setColor(79);
	}
	printText("  Yes!  ", x + 7, y + 2);
	common::setColor(Black);
	if (flag == 1) {
		common::setColor(47);
	}
	printText("  No~~  ", x + 25, y + 2);
	common::setColor(Black);
}

void menu::exitSelection() {
	int selectedOption = 0;
	int x = 38, y = 16;
	common::showCursor(false);

	while (1) {
		menu::exitScreen(selectedOption, x, y);
		int a = getInput();
		common::playSound(Move);
		if (a == 2) {
			selectedOption = (selectedOption - 1 + 2) % 2;
		}
		else if (a == 4) {
			selectedOption = (selectedOption + 1) % 2;
		}
		else if (a == 5) {
			common::playSound(Select);
			break;
		}
	}

	switch (selectedOption) {
	case 0:
		common::gotoXY(x, y + 4);
		exit(0);
		break;
	case 1:
		menu::clearConsole();
		menu::menuSelection();
		break;
	default: break;
	}
}

void menu::clearConsole() {
	system("cls");
}

void menu::printRectangle(int left, int top, int width, int height) {
	common::gotoXY(left, top);
	putchar(201);
	for (int i = 0; i < width; i++)
		putchar(205);
	putchar(187);

	int i = 0;
	for (i = 0; i < height; i++) {
		common::gotoXY(left, top + i + 1);
		putchar(186);
		common::gotoXY(left + width + 1, top + i + 1);
		putchar(186);
	}

	common::gotoXY(left, top + i);
	putchar(200);
	for (i = 0; i < width; i++)
		putchar(205);
	putchar(188);
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
