#ifndef SPLASHSCREENCLASS_H
#define SPLASHSCREENCLASS_H
/**
*/
#include <SFML/Graphics.hpp>

/** \class splashScreenClass
 *  \brief  A presentation class that uses the SFML library to display playing
 *          instructions and the game's title.
 *  \author 1932442 Bophilo Ntsemi and 1839578 Masilo Sekhele
 *  \version 3.0
*/

class splashScreenClass
{
    public:
        /**\fn splashScreenClass();
         * \brief Default constructor that creates a SplashScreen object.
         */
        splashScreenClass();

        /** \fn void setplashScreenAssets(sf::RenderWindow& render_splash);
         * \brief set the image textures and Fonts used to display on the SplashScreen window.
         *  \param render_splash is of type sf::RenderWindow.
         */
        void setplashScreenAssets(sf::RenderWindow& render_splash);

        /** \brief Displays the SplashScreen window.
         *  \param render_window is of type sf::RenderWindow.
         */
        void drawplashScreen(sf::RenderWindow& render_splash);

        /** \fn ~splashScreenClass();
         * \brief Default destructor that destroys a SplashScreen object.
         */
        ~splashScreenClass();

    private:
        /** // private variables
        */
        sf::Texture splashBackgroundTexture_;
        sf::Texture splashcontrollerTexture_;
        sf::Font splashFont_;
        sf::Text splash_Message;
        sf::Text continueGamePlayMessage;
        sf::Sprite centipede_cover1;
        sf::Sprite controller;

};

#endif // SPLASHSCREENCLASS_H
