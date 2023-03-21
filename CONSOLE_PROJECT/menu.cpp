#include "menu.h"

//cac lua chon trong menu
string options[] = { "PLAY GAME", "LOAD GAME", "ABOUT","HELP", "EXIT" };
//cac che do choi
string gameMode[] = { "PvP","PvC(easy)","PvC(hard)" };
//man hinh chinh
//man hinh gioi thieu thong tin va luat choi
void menu::helpScreen() {
	common::showCursor(false);
	//common::setColor(White);
	menu::clearConsole();
	int left = 13, top = 2, width = 81, height = 23;
	int line1 = 6, line2 = 19, line3 = 24;
	menu::printRectangle(left, top, width, height);
	common::gotoXY(left + 1, line1);
	for (int i = 0; i < width; i++) {
		putchar(196);
	}
	common::gotoXY(left + 1, line2);
	for (int i = 0; i < width; i++) {
		putchar(196);
	}
	for (int i = 1; i < height; i++) {
		common::gotoXY(line3, top + i);
		putchar(179);
	}
	common::gotoXY(line3, line1);
	putchar(197);
	common::gotoXY(line3, line2);
	putchar(197);

	//common::setColor(Red);
	common::gotoXY(left + 2, top + 2);
	cout << "Di chuyen:";
	common::gotoXY(left + 20, top + 1);
	putchar(249); cout << "Len tren:    W";
	common::gotoXY(left + 52, top + 1);
	putchar(249); cout << "Xuong duoi:  S";
	common::gotoXY(left + 20, top + 3);
	putchar(249); cout << "Sang trai:   A";
	common::gotoXY(left + 52, top + 3);
	putchar(249); cout << "Sang phai:   D";

	common::gotoXY(left + 2, top + 10);
	cout << "Luat choi";
	common::gotoXY(left + 13, top + 5);
	int left1 = left + 13;
	putchar(249); cout << " Nguoi choi chon ki hieu X se di truoc";
	common::gotoXY(left1, top + 6);
	cout << " Sau do den luot cua nguoi choi chon ki tu O.";
	common::gotoXY(left1, top + 8);
	putchar(249); cout << " Hai nguoi choi lan luot dat quan co cua minh ";
	common::gotoXY(left1, top + 9);
	cout << " len cac o trong.";
	common::gotoXY(left1, top + 11);
	putchar(249); cout << " Nguoi choi dau tien dat duoc 5 quan co lien tiep ";
	common::gotoXY(left1, top + 12);
	cout << " tren cung mot hang ma khong bi chan hai dau boi quan co cua ";
	common::gotoXY(left1, top + 13);
	cout << " doi phuong se chien thang tro choi.";

	common::gotoXY(left + 2, top + 20);
	cout << "Thong tin";
	common::gotoXY(left + 13, top + 18);
	cout << "Giao vien: Truong Toan Thinh";
	common::gotoXY(left + 13, top + 19);
	cout << "Thanh vien nhom:";
	common::gotoXY(left + 13, top + 20);
	cout << "+ Ngo Hoang Nam Hung (22127141)     + Le Thanh Minh Tri (22127422) ";
	common::gotoXY(left + 13, top + 21);
	cout << "+ Nguyen Khanh Toan  (22127418)     + Cao Hoang Loc     (22127234) ";

	//common::setColor(Black);
	menu::printRectangle(49, 27, 8, 2);
	//common::setColor(Red);
	common::gotoXY(47, 28);
	putchar(175);
	common::gotoXY(52, 28);
	cout << "Back";
	common::gotoXY(60, 28);
	putchar(174);
	while (getInput() != 5) {
		common::playSound(0);
	}
}

void menu::clearConsole() {
	system("cls");
}

void menu::printRectangle(int left, int top, int width, int height) {
	common::gotoXY(left, top);
	putchar(218);
	for (int i = 0; i < width; i++)
		putchar(196);
	putchar(191);

	int i = 0;
	for (i = 0; i < height; i++) {
		common::gotoXY(left, top + i + 1);
		putchar(179);
		common::gotoXY(left + width + 1, top + i + 1);
		putchar(179);
	}

	common::gotoXY(left, top + i);
	putchar(192);
	for (i = 0; i < width; i++)
		putchar(196);
	putchar(217);
}

void menu::mainScreen() {
	int x = 51, y = 14;
	common::setColor(Blue);
	menu::printLogo();
	common::setColor(Black);
	menu::printOptionsBoard();
	common::setColor(Red);
	printText(options[0], x + 1, y);
	printText(options[1], x + 1, y + 2);
	printText(options[2], x + 3, y + 4);
	printText(options[3], x + 3, y + 6);
	printText(options[4], x + 3, y + 8);
	common::gotoXY(x + 3, y + 10);
}
void menu::drawGameMode() {
	int x = 51, y = 14;
	common::setColor(Blue);
	menu::printLogo();
	common::setColor(Black);
	menu::printModeBoard();
	printText(gameMode[0], x + 4, y);
	printText(gameMode[1], x + 1, y + 2);
	printText(gameMode[2], x + 1, y + 4);
}
void menu::printModeBoard() {
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


	for (int i = 1; i < 6; i++)
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
	common::gotoXY(left, top + 6);
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
	32,32,32,32,223,219,219,219,219,219,219,223,32,223,32,222,219,221,32,32,32,32,32,32,219,219,32,32,32,219,219,32,221,32,32,32,254,219,219,32,32,32,32,223,219,219,219,219,219,219,223,32 };
	int top = 4, left = width / 2 - 26;
	int num_lines = 6, num_chars = 52;
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


	for (int i = 1; i < 10; i++)
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
	common::gotoXY(left, top + 10);
	putchar(200);
	for (int i = 1; i < 12; i++)
	{
		putchar(205);
	}
	putchar(188);
}

//void menu::helpScreen() {
//	common::setColor(Blue);
//	menu::printLogo();
//
//	int x = 18;
//	int y = 12;
//	int left = 17, top = 11, width = 86, height = 14;
//	common::setColor(Black);
//	menu::printRectangle(left, top, width, height);
//	printText(" ================================= HUONG DAN ==================================", x, y);
//	printText(" - Tro choi su dung hai ki hieu 'X','O' de dai dien cho hai nguoi choi.", x, ++y);
//	printText(" - Trong muc menu su dung cac phim 'A', 'S', 'Enter' de di chuyen va chon. ", x, ++y);
//	printText(" - Chon 'PLAY Game' de bat dau tro choi.                                       ", x, ++y);
//	printText(" - Nguoi choi su dung cac phim 'S' de di chuyen xuong duoi, 'W' de di chuyen", x, ++y);
//	printText(" len tren, 'A' de di chuyen sang trai, 'D' de di chuyen sang phai.", x, ++y);
//	++y;
//	printText(" ================================= LUAT CHOI ==================================", x, ++y);
//	printText(" - Hai nguoi choi  lan luot di chuyen va chon vao cac o chua duoc danh. ", x, ++y);
//	printText(" - Nguoi choi se chien thang tro choi khi nguoi choi do co 5 quan co lien tiep nhau", x, ++y);
//	printText(" theo hang ngang, hang doc hoac hang cheo ma khong bi chan o hai dau", x, ++y);
//	printText(" - Khi tat ca cac o tren ban co deu kin ma chua ai chien thang thi game dau hoa nhau.", x, ++y);
//	printText(" - Chuc cac ban choi game vui ve. An ESC de tro ve menu chinh.", x, ++y);
//
//}
void menu::aboutScreen() {
	common::setColor(Blue);
	menu::printLogo();
	common::setColor(Black);
	printText("ABOUT", 57, 12);
	printText("=============== DO AN CARO ===============", 39, 14);
	printText("  TRUONG DAI HOC KHOA HOC TU NHIEN", 43, 15);

	printText("==========  GIAO VIEN HUONG DAN ==========", 39, 18);
	printText(" THAY TRUONG TOAN THINH", 48, 19);
	printText("============  NHOM 22 - 20CTT3 ============", 39, 21);
	printText("22127141 - NGO HOANG NAM HUNG", 46, 22);
	printText("22127234 - CAO HOANG LOC", 46, 23);
	printText("22127422 - LE THANH MINH TRI", 46, 24);
}
////thay doi lua chon, truyen tham so direction 0 de di len hoac 1 de di xuong
//void menu::changeOption(bool direction, bool flag) {
//
//}