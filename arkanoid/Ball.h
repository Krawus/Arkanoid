#ifndef BALL_H
#define BALL_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Racket.h"
#include <cmath>
#include <vector>
#include "Bricks.h"

class Ball : public sf::CircleShape
{
public:

    Ball(sf::RenderWindow &window, Racket &racket);

    void Bounce(const sf::Time &time_, Racket &racket, const std::vector<std::unique_ptr<Brick>> &bricks, sf::Clock &clock_);

    void starting_on(Racket &racket)
    {
         starting_pos = true;
         setPosition(racket.getPosition().x+40,racket.getPosition().y-20);
    }
    void starting_off()
    {
        starting_pos = false;
    }

    bool check_starting()
    {
        return starting_pos;
    }

    void restartSpeed()
    {
        x_speed = 170;
        y_speed = 350;
    }


private:

    sf::RenderWindow &window_;

    int bound_L = 0;
    int bound_T = 35;
    int bound_R = window_.getSize().x;
    int bound_B = window_.getSize().y;


    sf::Texture texture_;

    int x_speed = 170;
    int y_speed = 350;
    int boost = 5;

    bool starting_pos = true;

};

#endif // BALL_H
