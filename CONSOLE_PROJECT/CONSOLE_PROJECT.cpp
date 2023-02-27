#include "game.h"

int main()
{
    int board[size][size]{};
    int x = 0, y = 0;
    bool XTurn = true;
    system("color F0");
    drawBoard();
    while (!win(board, x, y) ) {
       // drawCharacter(board);
        move(board, x, y, XTurn);
    }
    system("cls");
    system("color 0F");
    if (win(board, x, y)) {
        if (XTurn)  cout << "O won!\n";
        else        cout << "X won!\n";
    } 
   // else if (draw(board)) cout << "Draw!\n";
    return 0;
}

