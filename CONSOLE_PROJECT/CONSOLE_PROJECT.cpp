#include "game.h"

int main()
{
    int board[size][size]{ 0 };
    int x = 0, y = 0;
    bool XTurn = true;
    system("color F0");
    drawBoard();
    while (!win(board, x, y)) {
        drawCharacter(board);
        move(board, x, y, XTurn);
    }
    system("cls");
    system("color 0F");
    if (XTurn)  cout << "O won!\n";
    else        cout << "X won!\n";
    return 0;
}

