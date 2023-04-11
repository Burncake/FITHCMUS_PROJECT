#include "common.h"

HWND common::consoleWindow = GetConsoleWindow();
HANDLE common::consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE common::consoleInput = GetStdHandle(STD_INPUT_HANDLE);

void common::setUpConsole()
{
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

void common::playSound(int i)
{
    static const wchar_t* fileName[7] = {
        L"resources/background.wav",
        L"resources/start.wav",
        L"resources/move.wav",
        L"resources/select.wav",
        L"resources/win.wav",
        L"resources/lose.wav",
        L"resources/draw.wav" };
    PlaySound(fileName[i], NULL, SND_FILENAME | SND_ASYNC);
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
    if (c == 'o' || c == 'O')               return 7; // save
    if (c == 'i' || c == 'I')               return 8; // load
    if (c == 'y' || c == 'Y')               return 9; // continue playing
    if (c == 'n' || c == 'N')               return 10;// no
                                            return 0; // default              
}
void printText(string text, int x, int y) 
{
    common::gotoXY(x, y);
    cout << text;
}

void putcharXY(int ch, int x, int y)
{
    common::gotoXY(x, y);
    putchar(ch);
}

void drawPixelXY(int ch, int x, int y)
{
    common::gotoXY(x + 30, y + 4);
    putchar(ch);
}

void drawPixel(int ch, unsigned char pix[])
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
