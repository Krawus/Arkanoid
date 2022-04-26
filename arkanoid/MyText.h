#ifndef MYTEXT_H
#define MYTEXT_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class MyText : public sf::Text
{
public:
    MyText(const std::string &toDisplay ="")
    {
        setString(toDisplay);
        setFillColor(sf::Color::Magenta);
        font_.loadFromFile("font/slkscr.ttf");
        setFont(font_);
        setOutlineColor(sf::Color::Black);
        setOutlineThickness(4);
    }

    void dispNum(const float &num);


private:
    sf::Font font_;
};

#endif // MYTEXT_H
