#include "menu.h"


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



////thay doi lua chon, truyen tham so direction 0 de di len hoac 1 de di xuong
//void menu::changeOption(bool direction, bool flag) {
//
//}