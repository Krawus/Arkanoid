#include "Racket.h"

Racket::Racket(sf::RenderWindow &window):window_(window)
{
    if(!texture_.loadFromFile("tekstury/paddleRed.png"))
        std::cerr<<"could not read Racket\n";

    setTexture(texture_);

    setPosition(window.getSize().x/2 - 52,window.getSize().y-50);

}

void Racket::Control(const sf::Time &time_)
{
    if((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
            ||sf::Keyboard::isKeyPressed(sf::Keyboard::A)) && getGlobalBounds().left >= bound_L)
    {
        move(-x_speed*time_.asSeconds(),0);
        moving_L = true;
        moving_R = false;
    }
    else
        moving_L = true;

    if((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
            ||sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            && getGlobalBounds().left+getGlobalBounds().width <= bound_R)
    {
        move(x_speed*time_.asSeconds(),0);
        moving_R = true;
        moving_L = false;
    }
    else
        moving_R=false;

}

void Racket::boost()
{
    x_speed+= boost_v;
}

void Racket::elongation(sf::Clock &clock_)
{
    if(collected_boost)
    {
        if(clock_.getElapsedTime().asSeconds()<5)
            setScale(2,1);
        else
        {
            collected_boost = false;
            setScale(1,1);
        }
    }
}
