#ifndef RACKET_H
#define RACKET_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class Racket : public sf::Sprite
{
public:

    Racket(sf::RenderWindow &window);
    void Control(const sf::Time &time_);

    bool isMoving_L(){return moving_L;}
    bool isMoving_R(){return moving_R;}

    void boost();

    int getspeed()
    {
        return x_speed;
    }

    void restartSpeed()
    {
        x_speed = 300;
    }

    void elongation(sf::Clock &clock_);

    void giveItLength()
    {
        collected_boost=true;
    }

private:

    sf::RenderWindow &window_;
    sf::Texture texture_;

    int x_speed=320;

    int bound_L = 0;
    int bound_R = window_.getSize().x;

    bool collected_boost = false;

    bool moving_L = false;
    bool moving_R = false;

    int boost_v=5;

};

#endif // RACKET_H
