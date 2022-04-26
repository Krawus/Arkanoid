#ifndef POWERUP_H
#define POWERUP_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Racket.h"

class PowerUp :public sf::Sprite
{
public:
    PowerUp( sf::RenderWindow &window, const float &x_pos,const float &y_pos):window_(window)
    {
        if(!texture_.loadFromFile("tekstury/power_up.png"))
            std::cerr<<"Could not load Power Up ;c\n";
        setTexture(texture_);
        setScale(0.5,0.5);
        setPosition(x_pos,y_pos);
    }

    void KeepMovin(sf::Time &time_)
    {
        move(0,400*time_.asSeconds());
        if(getGlobalBounds().top>=window_.getSize().y)
            disappear = true;
    }



    void letDisappear()
    {
        disappear = true;
    }

    bool ShouldDisappear()
    {
        return disappear;
    }

private:
    sf::Texture texture_;
    sf::RenderWindow &window_;

    bool disappear = false;
};

#endif // POWERUP_H
