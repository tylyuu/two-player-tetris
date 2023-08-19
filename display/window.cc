#include "window.h"
#include <iostream>

SfmlWindow::SfmlWindow(int width, int height): width{width}, height{height} {
    window.create(sf::VideoMode(width, height), "SFML Window");
    colours[White] = sf::Color::White;
    colours[Black] = sf::Color::Black;
    colours[Red] = sf::Color::Red;
    colours[Green] = sf::Color::Green;
    colours[Blue] = sf::Color::Blue;
    colours[Cyan] = sf::Color::Cyan;
    colours[Yellow] = sf::Color::Yellow;
    colours[Magenta] = sf::Color::Magenta;
    colours[Orange] = sf::Color(255, 165, 0);
    colours[Brown] = sf::Color(165, 42, 42);
    colours[DarkGreen] = sf::Color(0, 100, 0);
    window.setActive(false);
}

SfmlWindow::~SfmlWindow() {}

void SfmlWindow::drawString(int x, int y, std::string msg, int size, int colour) {
    sf::Font font;
    if (!font.loadFromFile("/Users/lvtianyue/Downloads/puppppy/puppytest/display/Handjet-Bold.ttf")) {
        std::cerr << "Could not load font" << std::endl;
    }
    sf::Text text(msg,font,size);
    text.setFillColor(colours[colour]);
    text.setPosition(x, y);
    window.draw(text);
}

void SfmlWindow::fillRectangle(int x, int y, int width, int height, int colour) {
    sf::RectangleShape rectangle(sf::Vector2f(width, height));
    rectangle.setFillColor(colours[colour]);
    rectangle.setPosition(x, y);
    window.draw(rectangle);
}

void SfmlWindow::drawBigString(int x, int y, std::string msg, int colour) {
    drawString(x, y, msg, 25, colour);
}

void SfmlWindow::drawVeryBigString(int x, int y, std::string msg, int colour) {
    drawString(x, y, msg, 50, colour);
}

void SfmlWindow::drawTinyString(int x, int y, std::string msg, int colour) {
    drawString(x, y, msg, 10, colour);
}
