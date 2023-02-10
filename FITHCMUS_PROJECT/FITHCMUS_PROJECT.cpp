#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;
#define size 79.277564
Sprite sCircle[50], sCross[50];

int main()
{
    RenderWindow window(VideoMode(800, 800), "Caro by Le Thanh Minh Tri");
    Texture board, circle, cross, gCircle;
    board.loadFromFile("images/caro_board.png");
    circle.loadFromFile("images/circle.png");
    cross.loadFromFile("images/cross.png");
    gCircle.loadFromFile("images/green_circle.png");
    Sprite sBoard(board), GC(gCircle);
    for (int i = 0; i < 50; i++) {
        sCircle[i].setTexture(circle);
        sCircle[i].setPosition(-100, -100);
        sCross[i].setTexture(cross);
        sCross[i].setPosition(-100, -100);
    }
    float posx = 3, posy = 3;
    int x = 0, y = 0, a = 0, b = 0;
    GC.setPosition(posx, posy);
    bool isMove = false, isSet = false, turn = true;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::W) {
                    isMove = true;
                    y--;
                    if (y < 0) y = 9;
                }
                if (event.key.code == Keyboard::A) {
                    isMove = true;
                    x--;
                    if (x < 0) x = 9;
                }
                if (event.key.code == Keyboard::S) {
                    isMove = true;
                    y++;
                    if (y > 9) y = 0;
                }
                if (event.key.code == Keyboard::D) {
                    isMove = true;
                    x++;
                    if (x > 9) x = 0;
                }
            }

            if (event.type == Event::KeyReleased) {
                if ((event.key.code == Keyboard::W) || (event.key.code == Keyboard::A) || (event.key.code == Keyboard::S) || (event.key.code == Keyboard::D))
                    isMove = false;
                if (event.key.code == Keyboard::Enter) {
                    if (turn) {
                        sCircle[a++].setPosition(posx + x * size, posy + y * size);
                        turn = false;
                    }
                    else {
                        sCross[b++].setPosition(posx + x * size, posy + y * size);
                        turn = true;
                    }
                }
            }
        }

        if (isMove) {
            GC.setPosition(posx + x * size, posy + y * size);
        }

        window.clear();
        window.draw(sBoard);
        window.draw(GC);
        for (int i = 0; i < 50; i++) {
            window.draw(sCircle[i]);
            window.draw(sCross[i]);
        }
        window.display();
    }

    return 0;
}
