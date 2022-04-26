#ifndef BRICKS_H
#define BRICKS_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

enum class Model
{
    Blue,
    Purple,
    Red,
    Yellow,
    Green

};


class Brick : public sf::Sprite
{
public:
    Brick(const Model &model, const float &position_x, const float&position_y);

    void devastate()
    {
        getHit = true;
    }

    bool isDevastated()
    {
        return getHit;
    }


private:
    sf::Texture texture_;
    bool getHit = false;

};

#endif // BRICKS_H
