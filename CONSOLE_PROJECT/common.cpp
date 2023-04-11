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
        L"resources/draw.wav"  };
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
    if (c == 'l' || c == 'L')               return 7; // save
    if (c == 't' || c == 'T')               return 8; // load
    if (c == 'y' || c == 'Y')               return 9; // continue playing
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

void printLogo() {
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