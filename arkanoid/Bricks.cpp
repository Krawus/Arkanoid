#include "Bricks.h"

Brick::Brick(const Model &model, const float &position_x, const float &position_y)
{
    setPosition(position_x,position_y);




    if(model == Model::Red)
    {
        if(!texture_.loadFromFile("tekstury/red.png"))
            std::cerr<<"Could not read red bricks\n";

    }
    if(model == Model::Purple)
    {
        if(!texture_.loadFromFile("tekstury/purple.png"))
            std::cerr<<"Could not read purple bricks\n";

    }
    if(model == Model::Green)
    {
        if(!texture_.loadFromFile("tekstury/green.png"))
            std::cerr<<"Could not read green bricks\n";
    }

    if(model == Model::Yellow)
    {
        if(!texture_.loadFromFile("tekstury/yellow.png"))
            std::cerr<<"Could not read yellow bricks\n";
    }

    if(model == Model::Blue)
    {
        if(!texture_.loadFromFile("tekstury/blue.png"))
            std::cerr<<"Could not read blue bricks\n";
    }
    setTextureRect(sf::IntRect(0,0,64,32));

    setTexture(texture_);


}
