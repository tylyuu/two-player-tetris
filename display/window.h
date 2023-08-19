#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;

class SfmlWindow {
    sf::RenderWindow window;
    sf::Font font;
    sf::Color colours[11];
    int width, height;

public:
    SfmlWindow(int width = 500, int height = 500);
    ~SfmlWindow();

    enum { White = 0, Black, Red, Green, Blue, Cyan, Yellow, Magenta,
        Orange, Brown, DarkGreen };

    bool isOpen() const {
        return window.isOpen();
    }

    bool pollEvent(sf::Event &event) {
        return window.pollEvent(event);
    }

    void clear(const sf::Color &color = sf::Color::Black) {
        window.clear(color);
    }

    void display() {
        window.display();
    }

    void close() {
        window.close();
    }
    void setInActive(){
        window.setActive(false);
    }

    void drawString(int x, int y, std::string msg, int size, int colour = Black);
    void drawBigString(int x, int y, std::string msg, int colour = Black);
    void drawVeryBigString(int x, int y, std::string msg, int colour = Black);
    void drawTinyString(int x, int y, std::string msg, int colour = Black);
    void fillRectangle(int x, int y, int width, int height, int colour = Black);
};

#endif
