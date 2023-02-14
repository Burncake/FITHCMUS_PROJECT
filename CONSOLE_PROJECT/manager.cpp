#include "manager.h"

void drawBoard()
{
    const int endRow = 41, endColumn = 21;
    for (int i = 1; i <= endColumn; i++) {
        for (int j = 1; j <= endRow; j++) {
            switch (j) {
            case 1:
                // Left column //
                if (i == 1) cout << char(218);
                else if (i == endColumn) cout << char(192);
                else if ((i - 1) % 2 == 0) cout << char(195);
                else cout << char(179);
                break;
            case endRow:
                // Right column //
                if (i == 1) cout << char(191);
                else if (i == endColumn) cout << char(217);
                else if ((i - 1) % 2 == 0) cout << char(180);
                else cout << char(179);
                break;
            default:
                if ((j - 1) % 4 == 0) {
                    if (i == 1) cout << char(194);
                    else if (i == endColumn) cout << char(193);
                    else if ((i - 1) % 2 == 0) cout << char(197);
                    else cout << char(179);
                }
                else if (i % 2) cout << char(196);
                else cout << " ";
            }
        }            
        cout << endl;
    }
}

void manager::fixConsoleWindow()
{
    HWND consoleWindow = GetConsoleWindow();
    LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
    style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
    SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void manager::gotoXY(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
