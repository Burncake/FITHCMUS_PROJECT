#include "common.h"

HWND common::consoleWindow = GetConsoleWindow();
HANDLE common::consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE common::consoleInput = GetStdHandle(STD_INPUT_HANDLE);

void common::setUpConsole()
{
	system("color F0");
    setTitle();
    setUpWindow();
    disableMaximize();
    disableScroll();
    disableMouseSelect();
    showCursor(FALSE);
    changeFont();
}

void common::setUpWindow()
{
    RECT rectClient, rectWindow;
    GetClientRect(consoleWindow, &rectClient), GetWindowRect(consoleWindow, &rectWindow);
    int width = 870,
        height = 520;
    int posX = (GetSystemMetrics(SM_CXSCREEN) - width) / 2,
        posY = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;
    MoveWindow(consoleWindow, posX, posY, width, height, TRUE);
}

void common::disableMaximize()
{
    LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
    style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
    SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void common::disableScroll()
{
    ShowScrollBar(consoleWindow, SB_BOTH, 0);
}

void common::disableMouseSelect()
{
    DWORD prev_mode;
    GetConsoleMode(consoleInput, &prev_mode);
    SetConsoleMode(consoleInput, ENABLE_EXTENDED_FLAGS |
        (prev_mode & ~ENABLE_QUICK_EDIT_MODE));
}

void common::showCursor(bool showFlag)
{
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleOutput, &cursorInfo);
    cursorInfo.bVisible = showFlag;
    SetConsoleCursorInfo(consoleOutput, &cursorInfo);
}

void common::setTitle()
{
    SetConsoleTitle(L"CARO GAME");
}

void common::gotoXY(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(consoleOutput, coord);
}

void common::setColor(int color)
{
    SetConsoleTextAttribute(consoleOutput, color);
}

void common::bgmusic(bool n) {
	if (!n) PlaySound(0, 0, 0);
	else PlaySound(L"resources/background.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

void common::playSound(int i)
{
	wstring fileName[6] = {
		 L"resources/start.wav",
		 L"resources/move.wav",
		 L"resources/select.wav",
		 L"resources/win.wav",
		 L"resources/lose.wav",
		 L"resources/draw.wav" };
	// Open sound files
	mciSendString(L"close sound", NULL, 0, NULL);
	wstring command = L"open \"" + fileName[i] + L"\" type waveaudio alias sound";
	mciSendString(command.c_str(), NULL, 0, NULL);

	//Play sound
	mciSendString(L"play sound", NULL, 0, NULL);
}

void common::changeFont() {
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;                   // Width of each character in the font
    cfi.dwFontSize.Y = 16;                  // Height
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void coutColored(string str, int color)
{
    common::setColor(color);
    cout << str;
    common::setColor(DEFAULTCOLOR);
}

void coutColored(char chr, int color)
{
    common::setColor(color);
    cout << chr;
    common::setColor(DEFAULTCOLOR);
}

int getInput()
{
    char c = _getch();

    if (c == 'w' || c == 'W' || c == 72)    return 1; // up
    if (c == 'a' || c == 'A' || c == 75)    return 2; // left
    if (c == 's' || c == 'S' || c == 80)    return 3; // down
    if (c == 'd' || c == 'D' || c == 77)    return 4; // right
    if (c == '\r' || c == ' ')              return 5; // select
    if (c == 27)                            return 6; // esc
    if (c == 'l' || c == 'L')               return 7; // save
    if (c == 't' || c == 'T')               return 8; // load
    if (c == 'y' || c == 'Y')               return 9; // yes
    if (c == 'n' || c == 'N')               return 10;// no
                                            return 0; // default              
}
void printText(string text, int x, int y) 
{
    common::gotoXY(x, y);
    cout << text;
}

void clearConsole()
{
    system("cls");
}

void printRectangle(int left, int top, int width, int height) {
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

void putcharXY(int ch, int x, int y)
{
    common::gotoXY(x, y);
    putchar(ch);
}

void drawLogoPixelXY(int ch, int x, int y)
{
    common::gotoXY(x + 30, y + 4);
    putchar(ch);
}

void drawLogoPixel(int ch, unsigned char pix[])
{
    int num, temp = 0;
    for (int i = 0; i < 6; i++) {
        num = temp;
        while (pix[num] != 0) {
            putcharXY(ch, 30 + pix[num], 4 + i);
            num++;
        }
        temp = ++num;
    }
}

void drawXY(int color, int ch, int x, int y)
{
    common::setColor(color);
    common::gotoXY(x, y);
    putchar(ch);
}

void drawRowPixel(int color, int ch, int num, int x, int y)
{
    common::setColor(color);
    for (int i = 0; i < num; i++)
        putcharXY(ch, x + i, y);
}

//logo caro
void printLogo() {
	//black pixel
	common::setColor(Black);
	unsigned char blackPixel[] = {
		6,7,8,9,10,21,30,31,32,33,34,35,36,45,46,47,48,49,0,
		12,19,23,30,38,43,51,0,
		4,17,25,30,36,51,0,
		4,19,20,21,22,23,24,25,30,31,34,43,51,0,
		4,12,17,43,51,0,
		6,7,8,9,10,17,25,30,38,45,46,47,48,49,0 };
	drawLogoPixel(pixel, blackPixel);

	//red pixel
	common::setColor(DarkRed);
	unsigned char redPixel[] = {
		0,
		11,22,29,32,42,0,
		3,16,0,
		3,29,33,42,50,0,
		3,11,16,42,0,
		11,16,29,0
	};
	drawLogoPixel(pixel, redPixel);

	//red down
	unsigned char redD[] = {
		4,19,28,43,0,
		2,15,17,36,40,0,
		34,41,0,
		1,14,47,0,
		23,28,49,0,
		36,0
	};
	drawLogoPixel(pixelDown, redD);
	drawLogoPixelXY(pixelDown, 0, 4);

	//red up
	unsigned char redU[] = {
		0,
		49,0,
		23,28,49,0,
		27,0,
		34,0,
		4,13,43,0
	};
	drawLogoPixel(pixelUp, redU);

	//blue pixel
	common::setColor(Cyan);
	unsigned char bluePixel[] = {
		0,
		5,13,20,31,33,39,52,0,
		26,31,44,52,0,
		5,26,32,35,44,52,0,
		5,13,18,31,52,0,
		18,26,31,39,0
	};
	drawLogoPixel(pixel, bluePixel);

	//blue down
	unsigned char blueD[] = {
		12,23,38,51,0,
		16,25,41,0,
		6,0,
		2,49,0,
		2,38,45,0,
		0
	};
	drawLogoPixel(pixelDown, blueD);

	//blue up
	unsigned char blueU[] = {
		0,
		45,0,
		19,0,
		28,0,
		6,27,0,
		12,14,51,0
	};
	drawLogoPixel(pixelUp, blueU);

	//black down pixel, red bg 
	common::setColor(blackRed);
	unsigned char blackRedD[] = {
		5,20,29,44,0,
		3,18,37,0,
		29,35,0,
		0,
		50,0,
		37,0
	};
	drawLogoPixel(pixelDown, blackRedD);

	//black up, red bg
	unsigned char blackRedU[] = {
		0,
		4,50,0,
		24,29,43,50,0,
		18,0,
		25,30,35,0,
		5,44,0
	};
	drawLogoPixel(pixelUp, blackRedU);

	//black down, blue bg
	common::setColor(blackCyan);
	unsigned char blackBlueD[] = {
		11,22,37,50,0,
		24,0,
		5,0,
		0,
		36,37,44,0,
		0
	};
	drawLogoPixel(pixelDown, blackBlueD);

	//black up, blue bg
	unsigned char blackBlueU[] = {
		0,
		44,0,
		18,0,
		0,
		26,0,
		11,50,0
	};
	drawLogoPixel(pixelUp, blackBlueU);

	//blue red
	common::setColor(redCyan);
	unsigned char redBlue[] = {
		0,
		0,
		42,0,
		16,0,
		5,24,29,0,
		0
	};
	drawLogoPixel(pixelUp, redBlue);

	//black
	common::setColor(Black);
	drawLogoPixelXY(223, 17, 3);
	drawLogoPixelXY(220, 48, 3);
	drawLogoPixelXY(220, 1, 4);
	drawLogoPixelXY(220, 15, 3);
}

void bigOScreen() {
	int x = 0, y = 13;
	int xB = 4, xR = 3;

	drawRowPixel(Black, pixelDown, 4, x, y);
	drawRowPixel(Cyan, pixelDown, 2, xB, y);

	drawRowPixel(Black, pixel, 9, x, ++y);
	xB += 5;
	drawRowPixel(blackCyan, pixelDown, 2, xB, y);
	drawXY(Black, pixelDown, 11, y);
	xB += 3;
	drawRowPixel(Cyan, pixelDown, 2, xB, y);

	drawRowPixel(Black, pixel, 14, x, ++y);
	xB += 2;
	drawRowPixel(blackCyan, pixelDown, 2, xB, y);
	drawRowPixel(Black, pixelDown, 2, xB + 2, y);
	xB += 4;
	drawRowPixel(Cyan, pixelDown, 2, xB, y);

	drawRowPixel(Black, pixel, 19, x, ++y);
	xB++;
	drawXY(blackCyan, pixelUp, xB, y);
	drawXY(Cyan, pixel, xB + 1, y);
	drawXY(Cyan, pixelUp, xB + 2, y);

	drawRowPixel(Black, pixel, 20, x, ++y);
	drawRowPixel(blackCyan, pixelDown, 2, ++xB, y);
	xB += 2;
	drawRowPixel(Cyan, pixelDown, 2, xB, y);

	drawRowPixel(Black, pixel, 23, x, ++y);
	xB++;
	drawXY(blackCyan, pixelDown, xB++, y);
	drawXY(Cyan, pixel, xB++, y);
	drawXY(Cyan, pixelDown, xB, y);

	drawRowPixel(Black, pixelUp, 3, x, ++y);
	drawRowPixel(blackRed, pixelUp, 2, xR, y);
	x += 5;
	drawRowPixel(Black, pixel, 20, x, y);
	drawXY(blackCyan, pixelDown, xB++, y);
	drawXY(Cyan, pixel, xB++, y);
	drawXY(Cyan, pixelDown, xB++, y);

	xR += 2;
	drawRowPixel(DarkRed, pixelDown, 2, xR, ++y);
	xR += 2;
	drawRowPixel(blackRed, pixelDown, 2, xR, y);
	xR += 4;
	x += 4;
	drawRowPixel(Black, pixel, 19, x, y);
	drawXY(blackCyan, pixelDown, xB, y);
	drawXY(Cyan, pixel, xB + 1, y);
	drawXY(Cyan, pixelDown, xB + 2, y);

	drawRowPixel(DarkRed, pixelUp, 2, xR, ++y);
	x += 6;
	xR += 2;
	drawRowPixel(blackRed, pixelUp, 2, xR++, y);
	drawRowPixel(Black, pixel, 13, x, y);
	drawRowPixel(blackCyan, pixelUp, 2, xB++, y);
	drawXY(Cyan, pixelUp, xB + 1, y);

	drawXY(DarkRed, pixelUp, xR++, ++y);
	drawXY(DarkRed, pixel, xR, y);
	drawXY(blackRed, pixelUp, xR + 1, y);
	x += 2;
	drawRowPixel(Black, pixel, 12, x, y);
	drawXY(blackCyan, pixelDown, xB++, y);
	drawXY(Cyan, pixel, xB, y);
	drawXY(Cyan, pixelDown, xB + 1, y);

	drawXY(DarkRed, pixelUp, xR++, ++y);
	drawXY(DarkRed, pixel, xR++, y);
	drawXY(DarkRed, pixelUp, xR++, y);
	drawRowPixel(Black, pixel, 13, x, y);
	x += 3;
	drawXY(blackCyan, pixelDown, xB++, y);
	drawXY(Cyan, pixel, xB, y);
	drawXY(Cyan, pixelDown, xB + 1, y);

	drawRowPixel(DarkRed, pixel, 2, xR++, ++y);
	drawRowPixel(Black, pixel, 11, x++, y);
	drawRowPixel(Cyan, pixel, 2, xB++, y);

	drawRowPixel(DarkRed, pixel, 2, xR++, ++y);
	drawRowPixel(Black, pixel, 11, x++, y);
	drawRowPixel(Cyan, pixel, 2, xB, y);

	drawRowPixel(DarkRed, pixel, 2, xR++, ++y);
	drawRowPixel(Black, pixel, 10, x, y);
	x += 2;
	drawRowPixel(Cyan, pixel, 2, xB++, y);

	drawXY(DarkRed, pixelDown, xR, ++y);
	drawXY(DarkRed, pixel, xR + 1, y);
	drawXY(blackRed, pixelDown, xR + 2, y);
	drawRowPixel(Black, pixel, 9, x--, y);
	drawRowPixel(blackCyan, pixelUp, 2, xB, y);
	drawRowPixel(Cyan, pixelUp, 2, xB + 2, y);

	drawRowPixel(DarkRed, pixelDown, 2, xR - 2, ++y);
	drawRowPixel(blackRed, pixelDown, 2, xR, y);
	drawRowPixel(Black, pixel, 10, x, y);
	drawRowPixel(Cyan, pixel, 2, xB, y);

	drawRowPixel(DarkRed, pixel, 2, xR, ++y);
	drawRowPixel(Black, pixel, 10, x, y);
	drawRowPixel(Cyan, pixel, 2, xB, y);

	//hole
	drawRowPixel(Black, pixelUp, 2, 9, 15);
	drawRowPixel(Black, pixelDown, 2, 9, 16);

	drawRowPixel(Black, pixelUp, 4, 14, 20);
	drawXY(White, pixel, 23, 20);
	drawXY(Black, pixelUp, 24, 20);
	drawRowPixel(Black, pixelDown, 2, 23, 21);

	drawRowPixel(White, pixel, 2, 19, 23);

	drawRowPixel(Black, pixelUp, 2, 24, 28);
}

void bigXScreen() {
	int x = 86, y = 0;
	int xR_L = 84, xR_R = 109, xB = 103;

	drawRowPixel(DarkRed, pixel, 2, xR_L, y);
	drawRowPixel(Black, pixel, 17, x, y);
	drawRowPixel(blackCyan, pixelDown, 2, xB++, y);
	drawRowPixel(Cyan, pixelDown, 2, xB + 1, y);
	drawRowPixel(DarkRed, pixel, 2, xR_R + 1, y);
	drawRowPixel(Black, pixel, 4, xR_R + 3, y);
	xR_L += 4;
	x += 5;

	drawXY(DarkRed, pixelUp, xR_L++, ++y);
	drawXY(DarkRed, pixel, xR_L, y);
	drawXY(blackRed, pixelUp, xR_L + 1, y);
	drawRowPixel(Black, pixel, 13, x, y);
	drawRowPixel(Cyan, pixel, 2, xB, y);
	drawRowPixel(DarkRed, pixel, 2, xR_R, y);
	drawRowPixel(Black, pixel, 5, xR_R + 2, y);
	x += 2;

	drawRowPixel(DarkRed, pixelDown, 2, xR_L, ++y);
	drawRowPixel(blackRed, pixelDown, 2, xR_L + 2, y);
	drawRowPixel(Black, pixel, 11, x++, y);
	drawRowPixel(blackCyan, pixelDown, 2, xB, y);
	drawRowPixel(DarkRed, pixel, 2, xR_R, y);
	drawRowPixel(Black, pixel, 5, xR_R + 2, y);

	drawRowPixel(DarkRed, pixelUp, 2, xR_L, ++y);
	drawXY(Black, pixelUp, xR_L + 2, y);
	xR_L += 3;
	drawRowPixel(blackRed, pixelUp, 2, xR_L, y);
	drawRowPixel(Black, pixel, 22, x, y);
	x += 3;
	xR_L += 2;

	drawXY(DarkRed, pixelUp, xR_L++, ++y);
	drawXY(DarkRed, pixel, xR_L, y);
	drawXY(blackRed, pixelUp, xR_L + 1, y);
	drawRowPixel(Black, pixel, 19, x, y);

	drawRowPixel(DarkRed, pixel, 2, xR_L, ++y);
	drawRowPixel(Black, pixel, 19, x, y);

	drawRowPixel(DarkRed, pixel, 2, xR_L + 3, ++y);
	drawRowPixel(Black, pixel, 16, x + 3, y);

	drawRowPixel(DarkRed, pixelDown, 2, xR_L, ++y);
	drawXY(Black, pixelDown, x, y);
	drawRowPixel(blackRed, pixelDown, 2, x + 1, y);
	drawRowPixel(Black, pixel, 16, x + 3, y);

	drawRowPixel(DarkRed, pixel, 2, xR_L, ++y);
	drawRowPixel(Black, pixel, 19, x, y);
	xR_L--;
	x--;

	drawRowPixel(DarkRed, pixelDown, 2, xR_L - 5, ++y);
	drawRowPixel(Black, pixelDown, 3, xR_L - 3, y);
	drawRowPixel(blackRed, pixelDown, 2, xR_L, y);
	drawRowPixel(Black, pixel, 20, x, y);
	xR_L -= 2;
	x -= 2;

	drawRowPixel(DarkRed, pixel, 2, xR_L, ++y);
	drawRowPixel(Black, pixel, 22, x--, y);
	xR_L -= 3;

	drawRowPixel(DarkRed, pixelDown, 2, xR_L--, ++y);
	drawRowPixel(blackRed, pixelDown, 2, xR_L + 2, y);
	drawRowPixel(Black, pixel, 24, x - 1, y);
	x -= 3;

	drawRowPixel(DarkRed, pixel, 2, xR_L, ++y);
	drawRowPixel(Black, pixel, 14, x, y);
	drawXY(blackCyan, pixelDown, xB, y);
	drawXY(Cyan, pixel, xB + 1, y);
	drawXY(Cyan, pixelDown, xB + 2, y);
	drawRowPixel(DarkRed, pixel, 2, xR_R, y);
	drawRowPixel(Black, pixel, 5, xR_R + 2, y);

	drawRowPixel(DarkRed, pixel, 2, xR_L, ++y);
	drawRowPixel(Black, pixel, 14, x, y);
	drawXY(blackCyan, pixelUp, xB, y);
	drawXY(Cyan, pixel, xB + 1, y);
	drawXY(Cyan, pixelUp, xB + 2, y);
	drawRowPixel(DarkRed, pixel, 2, xR_R, y);
	drawRowPixel(Black, pixel, 5, xR_R + 2, y);
	xR_L -= 6;

	drawRowPixel(DarkRed, pixelDown, 2, xR_L, ++y);
	drawRowPixel(Black, pixelDown, 4, xR_L + 2, y);
	drawRowPixel(blackRed, pixelDown, 2, x - 2, y);
	drawRowPixel(Black, pixel, 13, x, y);
	drawXY(blackCyan, pixelUp, --xB, y);
	drawXY(Cyan, pixel, xB + 1, y);
	drawXY(Cyan, pixelUp, xB + 2, y);
	drawXY(DarkRed, pixelUp, xR_R++, y);
	drawXY(DarkRed, pixel, xR_R++, y);
	drawXY(blackRed, pixelUp, xR_R++, y);
	drawRowPixel(Black, pixel, 4, xR_R, y);
	x -= 6;

	drawRowPixel(DarkRed, pixelUp, 2, xR_L - 2, ++y);
	drawRowPixel(blackRed, pixelUp, 2, xR_L, y);
	drawRowPixel(Black, pixel, 17, x, y);
	drawRowPixel(blackCyan, pixelDown, 2, xB - 2, y);
	drawRowPixel(Cyan, pixelDown, 2, xB, y);
	drawRowPixel(DarkRed, pixel, 2, xR_R, y);
	drawRowPixel(Black, pixel, 2, xR_R + 2, y);

	drawRowPixel(DarkRed, pixel, 2, xR_L, ++y);
	drawRowPixel(Black, pixel, 17, x, y);
	drawXY(blackCyan, pixelUp, xB - 2, y);
	drawXY(Black, pixelUp, xB - 1, y);
	drawRowPixel(Cyan, pixelUp, 2, xB, y);
	drawXY(DarkRed, pixelUp, xR_R, y);
	drawRowPixel(DarkRed, pixel, 2, ++xR_R, y);
	drawXY(Black, pixel, xR_R + 2, y);

	//hole
	drawRowPixel(White, pixel, 3, 92, 0);
	drawRowPixel(Black, pixelUp, 2, 99, 0);
	drawRowPixel(Black, pixelUp, 3, 98, 3);
	drawRowPixel(Black, pixelDown, 3, 98, 4);
	drawRowPixel(Black, pixelUp, 3, 104, 10);
	drawXY(Black, pixelUp, 101, 13);
	drawXY(Black, pixelDown, 101, 14);
	drawRowPixel(Black, pixelUp, 3, 91, 14);
	drawRowPixel(Black, pixelDown, 3, 91, 15);
	drawRowPixel(Black, pixelUp, 2, 98, 15);
	drawRowPixel(Black, pixelDown, 2, 98, 16);
}

void particles() {
	drawXY(DarkRed, pixelDown, 5, 1);
	drawRowPixel(Black, pixelDown, 2, 6, 1);
	drawXY(Cyan, pixelDown, 8, 1);
	drawXY(Black, pixelDown, 10, 1);
	drawXY(Cyan, pixelDown, 11, 1);

	drawXY(DarkRed, pixelUp, 1, 3);
	drawRowPixel(blackRed, pixelUp, 2, 2, 3);
	drawRowPixel(Black, pixel, 4, 4, 3);
	drawRowPixel(blackCyan, pixelDown, 2, 8, 3);
	drawXY(Cyan, pixelDown, 10, 3);

	drawXY(DarkRed, pixelDown, 14, 3);
	drawRowPixel(Black, pixelDown, 6, 15, 3);
	drawRowPixel(Cyan, pixelDown, 2, 21, 3);

	drawXY(DarkRed, pixel, 5, 6);
	drawXY(Black, pixel, 6, 6);
	drawXY(blackCyan, pixelUp, 7, 6);
	drawXY(Cyan, pixelUp, 8, 6);
	drawXY(DarkRed, pixelDown, 10, 6);
	drawXY(Black, pixelDown, 11, 6);
	drawRowPixel(Cyan, pixelDown, 2, 12, 6);

	drawXY(DarkRed, pixelDown, 18, 7);
	drawRowPixel(Black, pixelDown, 4, 19, 7);
	drawXY(Cyan, pixelDown, 23, 7);

	drawXY(DarkRed, pixelUp, 10, 10);
	drawXY(Black, pixel, 11, 10);
	drawXY(Cyan, pixel, 12, 10);

	drawXY(DarkRed, pixel, 14, 10);
	drawRowPixel(Black, pixel, 2, 15, 10);
	drawXY(Cyan, pixelDown, 17, 10);

	drawRowPixel(DarkRed, pixelDown, 2, 36, 12);
	drawRowPixel(Black, pixelDown, 2, 38, 12);
	drawXY(Cyan, pixelDown, 41, 12);

	drawXY(DarkRed, pixel, 32, 16);
	drawRowPixel(Black, pixel, 3, 33, 16);
	drawXY(Cyan, pixel, 36, 16);

	drawXY(DarkRed, pixel, 38, 16);
	drawXY(Cyan, pixel, 39, 16);

	drawXY(DarkRed, pixelUp, 38, 23);
	drawXY(Black, pixelUp, 39, 23);
	drawXY(Cyan, pixelUp, 40, 23);

	drawXY(DarkRed, pixel, 42, 23);
	drawXY(Black, pixel, 43, 23);
	drawXY(Cyan, pixel, 44, 23);

	drawXY(DarkRed, pixel, 72, 13);
	drawXY(blackRed, pixelDown, 73, 13);
	drawXY(Black, pixel, 74, 13);
	drawXY(blackCyan, pixelUp, 75, 13);
	drawXY(Cyan, pixelUp, 76, 13);

	drawXY(DarkRed, pixel, 68, 19);
	drawRowPixel(Black, pixel, 2, 69, 19);
	drawXY(Cyan, pixel, 71, 19);
	drawXY(Cyan, pixelUp, 72, 19);

	drawXY(DarkRed, pixel, 78, 26);
	drawRowPixel(Black, pixel, 3, 79, 26);
	drawXY(Cyan, pixel, 82, 26);

	drawXY(DarkRed, pixel, 84, 21);
	drawXY(Black, pixel, 85, 21);
	drawXY(Cyan, pixel, 86, 21);

	drawXY(DarkRed, pixel, 104, 20);
	drawRowPixel(Black, pixel, 2, 105, 20);
	drawXY(Cyan, pixel, 107, 20);

	drawXY(DarkRed, pixelDown, 88, 21);
	drawXY(Cyan, pixelDown, 89, 21);

	drawXY(DarkRed, pixelDown, 96, 24);
	drawRowPixel(Black, pixelDown, 3, 97, 24);
	drawXY(Cyan, pixelDown, 100, 24);
}