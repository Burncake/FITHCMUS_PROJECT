#include "game.h"

void drawBoard()
{
    const int endRow = 4 * size + 1, endColumn = 2 * size + 1;
    for (int i = 1; i <= endColumn; i++)
        for (int j = 1; j <= endRow; j++) {
            gotoXY(j + 3, i + 1);
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

void move(int board[][size], int& x, int& y, bool& XTurn)
{
    gotoXY(6 + 4 * x, 3 + 2 * y);
    if (board[y][x] == 0) {
        if (XTurn)  coutChrColored(char(42), PointerColor);
        else        coutChrColored(char(248), PointerColor);
    }
    if (board[y][x] == 1) coutStrColored("X", PointerColor);
    if (board[y][x] == 2) coutStrColored("O", PointerColor);
    char c;
    c = _getch();
    switch (c) {
    case 'w':
        y--;
        if (y < 0) y = size - 1;
        break;
    case 'a':
        x--;
        if (x < 0) x = size - 1;
        break;
    case 's':
        y++;
        if (y > size - 1) y = 0;
        break;
    case 'd':
        x++;
        if (x > size - 1) x = 0;
        break;
    case '\r':
        processBoard(board, x, y, XTurn);
        break;
    }
}

void drawCharacter(int board[][size]) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++) {
            gotoXY(6 + 4 * j, 3 + 2 * i);
            if (board[i][j] == 0) cout << " ";
            if (board[i][j] == 1) coutStrColored("X", DarkBlue);
            if (board[i][j] == 2) coutStrColored("O", DarkRed);
        }
}

void processBoard(int board[][size], int x, int y, bool& XTurn) {
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