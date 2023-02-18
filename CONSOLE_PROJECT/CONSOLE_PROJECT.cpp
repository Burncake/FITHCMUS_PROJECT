#include "game.h"

int main()
{
    int board[size][size]{ 0 };
    int x = 0, y = 0;
    bool XTurn = true;
    system("color F0");
    drawBoard();
    while (1) {
        drawCharacter(board);
        move(board, x, y, XTurn);
    }
}

