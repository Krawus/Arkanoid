#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Racket.h"
#include "Bricks.h"
#include "Ball.h"
#include "MyText.h"
#include <string>
#include <cmath>
#include <memory>
#include <vector>
#include "Logo.h"
#include <fstream>
#include <random>
#include "PowerUp.h"


int RND(const int &min, const int &max)
{

    static std::random_device ran_dev{};
    std::default_random_engine engine{ran_dev()};
    std::uniform_int_distribution<int>dist{min,max};

    return dist(engine);


}

std::string trim_score(const float &elapsed)
{
    auto time_to_disp = std::to_string(elapsed);
    std::string real;

    if(elapsed == 0)
     real = time_to_disp.substr(0,1);
    if(elapsed<10 && elapsed>0)
    real = time_to_disp.substr(0,4);
    if(elapsed>10 && elapsed<100)
    real = time_to_disp.substr(0,5);
    if(elapsed >100 && elapsed<1000)
    real = time_to_disp.substr(0,6);
    if(elapsed>1000&&elapsed<10000)
        real = time_to_disp.substr(0,7);

    return real;
}


std::vector<std::unique_ptr<Brick>> generate_bricks()
{
    std::vector<std::unique_ptr<Brick>>bricks;
    float start_x = -15;
    for(int i = 0; i<11; i++)
    {
        start_x+=65;
        bricks.emplace_back(std::make_unique<Brick>(Model::Red,start_x,167));
    }
    start_x = -50;
    for(int i =0; i<12; i++)
    {
        start_x+=65;
        bricks.emplace_back(std::make_unique<Brick>(Model::Yellow,start_x,200));
    }
    start_x = -50;

    for(int i = 0; i<12; i++)
    {
        start_x+=65;
        bricks.emplace_back(std::make_unique<Brick>(Model::Green,start_x,233));
    }

    start_x = -15;
    for(int i = 0; i<11; i++)
    {
        start_x+=65;
        bricks.emplace_back(std::make_unique<Brick>(Model::Blue,start_x,266));
    }
    start_x = 145;
    for(int i =0 ; i<6; i++)
    {
        start_x+=65;
        bricks.emplace_back(std::make_unique<Brick>(Model::Purple,start_x,299));
    }




    return bricks;


}

void restart(Ball &ball, Racket &racket, int &Lives_)
{
    ball.starting_on(racket);
    Lives_ = 3;

}

std::vector<std::unique_ptr<MyText>> start_restart()
{

    std::vector<std::unique_ptr<MyText>> vec_;
    std::unique_ptr<MyText> text1 = std::make_unique<MyText>("Press Space to release the ball");
    text1->setOrigin(text1->getGlobalBounds().left+text1->getGlobalBounds().width, text1->getGlobalBounds().top+text1->getGlobalBounds().height);
    text1->setPosition(670,500);
    text1->setFillColor(sf::Color::Red);
    text1->setCharacterSize(33);
    text1->setStyle(sf::Text::Bold);


    std::unique_ptr<MyText> text2 = std::make_unique<MyText>("Press Enter to restart");
    text2->setOrigin(text2->getGlobalBounds().left+text2->getGlobalBounds().width, text2->getGlobalBounds().top+text2->getGlobalBounds().height);
    text2->setPosition(580,500);
    text2->setFillColor(sf::Color::Red);
    text2->setCharacterSize(33);
    text2->setStyle(sf::Text::Bold);


     vec_.emplace_back(std::move(text1));
     vec_.emplace_back(std::move(text2));

     return vec_;


}

float load_score()
{
    std::fstream high_file("highscore.txt");
            if(!high_file.is_open())
            {
                std::cerr<<"fail to load highscore\n";
                return 99999;
            }
            else
            {
                std::string hi_text;
                 high_file >> hi_text;
                 if(hi_text.size()>0)
                 return std::stof(hi_text);
                 else
                     return 999999;

            }
}


void update_highscore( float &hi_, const float &elapsed_)
{
    if(elapsed_ < hi_)
    {
        hi_=elapsed_;
        std::ofstream out("highscore.txt", std::ios::trunc);
        if(out.is_open())
        {
            out<<hi_;
        }
        else
            std::cerr<<"saving highscore failed, file is corrupted\n";
    }

}







int main() {



    std::vector<std::unique_ptr<PowerUp>> power_up;
    float highscore=load_score();


    sf::Sprite background;
    sf::Texture back_t;
    if (!back_t.loadFromFile("tekstury/beach.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    background.setTexture(back_t);

      sf::SoundBuffer buffer_main;
      buffer_main.loadFromFile("music/main_theme.wav");

       sf::Sound main_music;
       main_music.setBuffer(buffer_main);
       main_music.play();
       main_music.setVolume(30);
       main_music.setLoop(true);


       sf::SoundBuffer buffer_hit;
       buffer_hit.loadFromFile("music/brick_hit.wav");

        sf::Sound hit_sound;
        hit_sound.setBuffer(buffer_hit);
        hit_sound.setVolume(45);




       auto bricks = generate_bricks();

       bool welcome = true;
       bool restart = false;
       bool newtime = true;
       bool win = false;

       int Lives = 3;

    // create the window
   sf::RenderWindow window(sf::VideoMode(800, 800), "ARKANOID v209 RELOADED FULL BURST: ULTIMATE BEACH EDITION");
    // run the program as long as the window is open





   std::vector<std::unique_ptr<MyText>> hi_bye = start_restart();
   auto logo = std::make_unique<Logo>(window,"tekstury/inscription.png");
   auto winscreen = std::make_unique<Logo>(window,"tekstury/win.png");
   winscreen->setScale(1,1);
   winscreen->setPosition(window.getSize().x/2,265);

   MyText Time_w("TIME: ");
   MyText Lives_w("LIVES: ");
   MyText press_toplay("Press enter to play");
   MyText press_tores("Press enter to restart");
   MyText hi_score_text("BEST TIME: ");
   MyText hi_score_number;

   if(highscore<999999)
       hi_score_number.setString(trim_score(highscore));


   hi_score_number.setFillColor(sf::Color::White);



   hi_score_text.setPosition(240,0);
   hi_score_number.setPosition(425,0);

   Lives_w.setPosition(670,0);

   MyText Lives_num;
   Lives_num.setFillColor(sf::Color::White);
   Lives_num.setPosition(770,0);
   MyText Time_t;

   Time_t.setPosition(85,0);
   Time_t.setFillColor(sf::Color::White);


   Racket racket(window);
   //Brick brick(Model::Yellow,100,200);
   Ball ball(window,racket);


    sf::Clock clock;
    sf::Clock all_game;
    sf::Clock racket_prolonger;
    sf::Clock speed_control;
    while (window.isOpen())
    {

        sf::Time frameTime = clock.restart();

        float elapsed = all_game.getElapsedTime().asSeconds();
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();


            if(!restart)
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                ball.starting_off();
                if(newtime)
                {
                    all_game.restart();
                    newtime = false;
                }
                welcome = false;

            }


            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
              {
                    restart = false;
                    welcome = true;
                    Lives = 3;
                    ball.starting_on(racket);
                    ball.restartSpeed();
                    racket.restartSpeed();
                    newtime = true;
                    bricks = generate_bricks();
              }


        }

        if(ball.getGlobalBounds().top>window.getSize().y)
        {
            Lives--;
            ball.starting_on(racket);
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...

        auto time_to_disp = trim_score(elapsed);

        Time_t.setString(time_to_disp);
        Lives_num.setString(std::to_string(Lives));

        racket.Control(frameTime);
        ball.Bounce(frameTime,racket,bricks,speed_control);








        window.draw(background);
        window.draw(racket);

        for(unsigned int i = 0 ; i<bricks.size(); i++)
        {
            if(bricks[i]->isDevastated())
            {


              if(power_up.size()==0)
              {
                  int num = RND(0,10);
                 if(num==7)
                     power_up.emplace_back(std::make_unique<PowerUp>(window,bricks[i]->getPosition().x, bricks[i]->getPosition().y));
              }
              hit_sound.play();
            bricks.erase(bricks.begin()+i);

            }


        }


        for(auto &b :bricks)
            window.draw(*b);

        for(unsigned int i = 0; i<power_up.size(); i++)
        {
            window.draw(*power_up[i]);
            power_up[i]->KeepMovin(frameTime);

            if(power_up[i]->getGlobalBounds().intersects(racket.getGlobalBounds()))
            {
                racket_prolonger.restart();
                racket.giveItLength();
                power_up[i]->letDisappear();
            }
            if(power_up[i]->ShouldDisappear())
                power_up.erase(power_up.begin()+i);
        }

        window.draw(ball);
        window.draw(Time_t);
        window.draw(Time_w);
        window.draw(Lives_w);
        window.draw(Lives_num);
        window.draw(hi_score_text);
        window.draw(hi_score_number);

        racket.elongation(racket_prolonger);


        if(welcome == true)
        {
            window.draw(*logo);
            window.draw(*hi_bye[0]);

        }


        if(Lives == 0)
        {
            restart = true;
            window.draw(*hi_bye[1]);


        }
        if(bricks.size()==0)
        {
            win = true;
            ball.starting_on(racket);
            restart = true;
            window.draw(*hi_bye[1]);
            window.draw(*winscreen);
            update_highscore(highscore,elapsed);
            hi_score_number.setString(trim_score(highscore));



        }







        window.display();
    }

    return 0;
}
