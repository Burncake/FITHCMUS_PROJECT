#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;
#define size 79.277564

int main()
{
    RenderWindow window(VideoMode(800, 800), "Caro by Le Thanh Minh Tri");
    Texture board, circle;
    board.loadFromFile("images/caro_board.png");
    circle.loadFromFile("images/green_circle.png");
    Sprite sBoard(board);
    Sprite sCircle(circle);
    double posx = 3, posy = 3;
    int x = 0, y = 0;
    sCircle.setPosition(posx, posy);
    bool isMove = false;

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
            if (event.type == Event::KeyReleased)
                if ((event.key.code == Keyboard::W) || (event.key.code == Keyboard::A) || (event.key.code == Keyboard::S) || (event.key.code == Keyboard::D))
                    isMove = false;
        }

        if (isMove) {
            sCircle.setPosition(posx + x * size, posy + y * size);
        }
        window.clear(Color::White);
        window.draw(sBoard);
        window.draw(sCircle);
        window.display();
    }

    return 0;
}
