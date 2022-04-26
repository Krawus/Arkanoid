#include "Ball.h"


Ball::Ball(sf::RenderWindow &window, Racket &racket):sf::CircleShape(11),window_(window)
{
    if(!texture_.loadFromFile("tekstury/ballG.png"))
        std::cerr<<"could not load ball texture\n";



    setTexture(&texture_);

    setPosition(racket.getPosition().x+40,racket.getPosition().y-20);

}

void Ball::Bounce(const sf::Time &time_, Racket &racket, const std::vector<std::unique_ptr<Brick>>&bricks, sf::Clock &clock_)
{

    if(starting_pos==true)
    {

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)||sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            if(getGlobalBounds().left>= 40)
            move(-racket.getspeed()*time_.asSeconds(),0);

        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)|| sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            if(getGlobalBounds().left+getGlobalBounds().width <= window_.getSize().x -40)
            move(racket.getspeed()*time_.asSeconds(),0);
        }
    }
    else{
        if(getPosition().y<=racket.getPosition().y + 10)
        {

    if(getGlobalBounds().left<=bound_L)
    {
        x_speed = std::abs(x_speed);
    }

    if(getGlobalBounds().left+getGlobalBounds().width >=bound_R)
    {
        x_speed = -std::abs(x_speed);
    }

    if(getGlobalBounds().top <= bound_T)
    {
        y_speed = std::abs(y_speed);

    }

    if((getGlobalBounds()).intersects(racket.getGlobalBounds()) && getGlobalBounds().top+getGlobalBounds().height <= racket.getGlobalBounds().top+20)
    {
        if(clock_.getElapsedTime().asSeconds()>0.3)
        {
        y_speed = std::abs(y_speed) + boost;
        clock_.restart();
        racket.boost();
        }
        y_speed = (-1)*std::abs(y_speed);



        if(getGlobalBounds().left+getRadius()<=racket.getGlobalBounds().left+21)
            x_speed= (-1)*std::abs(x_speed);

        if(getGlobalBounds().left+getRadius()>=racket.getGlobalBounds().left+racket.getGlobalBounds().width-21)
            x_speed=std::abs(x_speed);
    }


        }
         move(x_speed*time_.asSeconds(),y_speed*time_.asSeconds());
    }




    for(auto &b : bricks)
        if(b->getGlobalBounds().intersects(getGlobalBounds()))
       {
            b->devastate();


      float imposition_Left = (getGlobalBounds().left+getGlobalBounds().width) - b->getGlobalBounds().left;
      float imposition_Right = (b->getGlobalBounds().left+b->getGlobalBounds().width) - (getGlobalBounds().left);
      float imposition_Top = getGlobalBounds().top+getRadius() - b->getGlobalBounds().top;
      float imposition_Bottom = (b->getGlobalBounds().top+b->getGlobalBounds().height) - (getGlobalBounds().top);

      bool moreFromLeft = std::abs(imposition_Left) < std::abs(imposition_Right);
      bool moreFromTop = std::abs(imposition_Top) < std::abs(imposition_Bottom);


      float impos_vertical;
      if(moreFromTop)
          impos_vertical = imposition_Top;
      else
          impos_vertical = imposition_Bottom;


      float impos_horizontal;
      if(moreFromLeft)
          impos_horizontal = imposition_Left;
      else
          impos_horizontal = imposition_Left;




      if(std::abs(impos_horizontal) < std::abs(impos_vertical))
      {
          if(moreFromLeft)
              x_speed = -std::abs(x_speed);
          else
              x_speed = std::abs(x_speed);

      }
      else
      {
          if(moreFromTop)
          {
              y_speed = -std::abs(y_speed);
          }
          else
              y_speed = std::abs(y_speed);
          }
                     move(x_speed*time_.asSeconds(),y_speed*time_.asSeconds());

    }



}
