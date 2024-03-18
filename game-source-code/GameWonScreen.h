#ifndef GAMEWONSCREEN_H
#define GAMEWONSCREEN_H

#include <SFML/Graphics.hpp>
#include <string>

/**	\class GameWonScreen
 * 	\brief  A presentation layer class that uses the SFML library to display the player's
 * 	victory and a summary of the game scores.
 *  \author 1932442 Bophilo Ntsemi and 1839578 Masilo Sekhele
 *  \version 3.0
 */
class GameWonScreen
{
    public:
        /** \fn GameWonScreen();
         * \brief Default constructor that creates a GameWonScreen object.
         */
        GameWonScreen();

        /** \fn void show(sf::RenderWindow& render_window, const int& player_score, const int& high_score);
         * \brief Displays the Game Won window.
         *  \param render_window is of type sf::RenderWindow.
         *  \param player_score is of type int. Holds the player's score.
         *  \param high_score is of type int. Holds the highest score achieved in the game.
         */
        void show(sf::RenderWindow& render_window, const int& player_score, const int& high_score);

        /** \fn ~GameWonScreen();
         * \brief Default destructor that deletes a GameWonScreen object.
         */
        ~GameWonScreen();

    private:
        sf::Texture gameWonTexture_;
        sf::Font font_;
};

#endif // GAMEWONSCREEN_H
