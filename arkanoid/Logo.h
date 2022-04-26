#ifndef LOGO_H
#define LOGO_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class Logo : public sf::Sprite
{
public:
    Logo(sf::RenderWindow &window, const std::string &path):window_(window)
    {

        if(!texture_.loadFromFile(path))
        {
            std::cerr<<"Could not load inscription\n";

        }
        setTexture(texture_);
        setOrigin((getGlobalBounds().left+getGlobalBounds().width)/2,(getGlobalBounds().top+getGlobalBounds().height)/2);
        setPosition(window_.getSize().x/2,window_.getSize().y/2);
        setScale(0.3,0.3);
    }
private:
    sf::RenderWindow &window_;
    sf::Texture texture_;

};

#endif // LOGO_H
