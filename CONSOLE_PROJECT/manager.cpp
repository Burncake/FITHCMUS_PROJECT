#include "manager.h"

void fixConsoleWindow()
{
    HWND consoleWindow = GetConsoleWindow();
    LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
    style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
    SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void gotoXY(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void move(int board[][12], int& x, int& y, bool& XTurn)
{
    gotoXY(6 + 4 * x, 3 + 2 * y);
    if (!board[y][x]) {
        if (XTurn) cout << char(42);
        else cout << char(248);
    }
    char c;
    c = _getch();
    switch (c) {
    case 'w':
        y--;
        if (y < 0) y = 11;
        break;
    case 'a':
        x--;
        if (x < 0) x = 11;
        break;
    case 's':
        y++;
        if (y > 11) y = 0;
        break;
    case 'd':
        x++;
        if (x > 11) x = 0;
        break;
    case '\r':
        processBoard(board, x, y, XTurn);
        break;
    }
}

void drawBoard()
{
    const int endRow = 49, endColumn = 25;
    for (int i = 1; i <= endColumn; i++) {
        for (int j = 1; j <= endRow; j++) {
            gotoXY(j + 3, i + 1);
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

void drawCharacter(int board[][12]) {
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            gotoXY(6 + 4 * j, 3 + 2 * i);
            if (board[i][j] == 1)
                cout << "X";
            if (board[i][j] == 2)
                cout << "O";
        }
    }
}

void processBoard(int board[][12], int x, int y, bool& XTurn) {
    if (board[y][x]) return;
    if (XTurn) {
        board[y][x] = 1;
        XTurn = false;
    }
    else {
        board[y][x] = 2;
        XTurn = true;
    }

}