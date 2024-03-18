#include "splashScreenClass.h"
#include <string>
using namespace std::literals::string_literals;
splashScreenClass::splashScreenClass()
{
  ///load resources for splash
  splashBackgroundTexture_.loadFromFile("resources/centipede cover1.png"s);
  splashcontrollerTexture_.loadFromFile("resources/Splash_Controls.png"s);
  splashFont_.loadFromFile("resources/Font.ttf"s);
  ///Ctor
}

void splashScreenClass::setplashScreenAssets(sf::RenderWindow& render_splash)
{
 auto halfConstant = 2.0f;

 ///set Font and Text messages
 splash_Message.setFont(splashFont_);
 splash_Message.setString("CENTIPEDE GAME");
 splash_Message.setCharacterSize(40);
 splash_Message.setStyle(sf::Text::Bold);
 splash_Message.setFillColor(sf::Color::Yellow);
 sf::FloatRect splashMessage_rect = splash_Message.getLocalBounds();
 splash_Message.setOrigin(splashMessage_rect.left+splashMessage_rect.width/halfConstant,
                       splashMessage_rect.top+splashMessage_rect.height/halfConstant);
 splash_Message.setPosition(render_splash.getSize().x/halfConstant, render_splash.getSize().y/10);

 continueGamePlayMessage.setFont(splashFont_);
 continueGamePlayMessage.setString("Continue => Enter   Quit => Escape");
 continueGamePlayMessage.setCharacterSize(20);
 continueGamePlayMessage.setFillColor(sf::Color::Yellow);
 continueGamePlayMessage.setStyle(sf::Text::Bold);
 splashMessage_rect = continueGamePlayMessage.getLocalBounds();
 continueGamePlayMessage.setOrigin(splashMessage_rect.left + splashMessage_rect.width/halfConstant,
   splashMessage_rect.top  + splashMessage_rect.height/halfConstant);
   continueGamePlayMessage.setPosition(render_splash.getSize().x/halfConstant, render_splash.getSize().y/1.09f);

 ///set background cover
  centipede_cover1.setTexture(splashBackgroundTexture_);
  centipede_cover1.setScale(sf::Vector2f{3.2, 2.4});
  centipede_cover1.setColor(sf::Color::Green);
  centipede_cover1.setOrigin(splashBackgroundTexture_.getSize().x/halfConstant, splashBackgroundTexture_.getSize().y/halfConstant);
  centipede_cover1.setPosition(render_splash.getSize().x/halfConstant, render_splash.getSize().y/halfConstant);

  ///set controller cover
  splashcontrollerTexture_.setSmooth(true);
  controller.setTexture(splashcontrollerTexture_);
  controller.scale(sf::Vector2f{1.0, 1.0});
  controller.setColor(sf::Color::Red);
  controller.setOrigin(splashcontrollerTexture_.getSize().x/halfConstant, splashcontrollerTexture_.getSize().y/halfConstant);
  controller.setPosition(render_splash.getSize().x/halfConstant, render_splash.getSize().y/halfConstant);
}///set

 void splashScreenClass::drawplashScreen(sf::RenderWindow& render_splash)
 {
     ///set colour effects variables
     auto colourEffects = true;
     auto delayTimer = 0;
     ///poll for keyboard events of spacebar and Escape pressed to start or quit game respectively.
     sf::Event event;
     while(true)
     {
        render_splash.clear(sf::Color::Black);
        if(colourEffects && delayTimer%30==0)
        {
            centipede_cover1.setColor(sf::Color::Red);
            splash_Message.setFillColor(sf::Color::Red);
            continueGamePlayMessage.setFillColor(sf::Color::Green);
            controller.setColor(sf::Color::Yellow);
            colourEffects = !colourEffects;
        }
        else if(!colourEffects && delayTimer%15==0)
        {
            centipede_cover1.setColor(sf::Color::Magenta);
            splash_Message.setFillColor(sf::Color::Green);
            continueGamePlayMessage.setFillColor(sf::Color::Yellow);
            controller.setColor(sf::Color::Red);
            colourEffects = !colourEffects;
        }

        ++delayTimer;
        render_splash.draw(centipede_cover1);
        render_splash.draw(splash_Message);
        render_splash.draw(continueGamePlayMessage);
        render_splash.draw(controller);
        render_splash.display();

        while(render_splash.pollEvent(event))
        {
           if(event.key.code==sf::Keyboard::Escape || event.type == sf::Event::Closed)
           {
               render_splash.close();
               return;
           }
           if(event.key.code == sf::Keyboard::Enter)
           {
             return;
           }
        }///while
     }///while
 }///draw

 splashScreenClass::~splashScreenClass()
{
   ///Dtor
}
