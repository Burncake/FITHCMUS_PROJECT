#include "manager.h"
int main()
{
    int board[12][12]{ 0 };
    int x = 0, y = 0;
    bool XTurn = true;
    system("color F0");
    while (1) {
        drawBoard();
        drawCharacter(board);
        move(board, x, y, XTurn);
    }
}

