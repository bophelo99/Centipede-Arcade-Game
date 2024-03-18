#ifndef logicLayerClass_H
#define logicLayerClass_H
/**
*/
#include "presentationLayerClass.h"
#include "gameStateClass.h"
#include "ScreenParameters.h"
#include "gameEngineClass.h"
#include "timerClass.h"
/**
*/
#include <ctime>
#include <memory>
/**
*/
using std::vector;
using std::shared_ptr;

/** \class logicLayerClass
 *  \brief This class uses GameEngine's function to perform the logic of the game.
 *         It tells resourceManager to load the game assets needed to present the game logic.
 *         It then presents the logic to the Presentation Layer for it to be rendered
 *         on the game screen. The game is controlled by this class.
 *  \author 1932442 Bophilo Ntsemi and 1839578 Masilo Sekhele
 *  \version 3.0
 */
class logicLayerClass
{
    public:
        /** \fn logicLayerClass();
         * \brief Default logicLayerClass constructor. An instance of the game is created
         *         and the game objects are initialized.
         */
        logicLayerClass();

        /** \fn ~logicLayerClass();
         * \brief Default Destructor. Destroys an instance of the game.
         */
       ~logicLayerClass();

        /** \fn void displayWelcomeSplashScreen();
         * \brief Displays the splash screen at the start of the game.
         */
        void displayWelcomeSplashScreen();

        /** \fn void displayGameObjects();
         * \brief Gives Presentation the game objects from the GameEngine class
         *         to be drawn.
         */
        void displayGameObjects();

        /** \fn gameStateClass getState();
         * \brief return the current game state
         *  \param currentGames_state of a struct typed gameStateClass.
        */
        gameStateClass getState();

        /** \fn void setResourcesInfo();
         * \brief Loads paths to the textures used by the game.
         */
        void setResourcesInfo();

        /** \fn void initializeGameObjects();
         * \brief Generates Mushrooms and plays the game start sound.
         */
        void initializeGameObjects();

        /** \fn void UpdateGamePlay();
         * \brief Runs the logic for the game.
         */
        void UpdateGamePlay();

        /** \fn void PocessInputkeys();
         * \brief Tells presentation to process input from keyboard.
         */
        void PocessInputkeys();

        /** \fn void levelUp();
         * \brief Plays the levelUp sound if the player's level has advanced.
         */
        void levelUp();

        /** \fn void reincarnateMushrooms();
         * \brief Reincarnates Mushroom objects in the game.
         */
        void reincarnateMushrooms();

        /** \fn void reincarnatePlayer();
         *  \brief Removes all moving entities from the game, resets the position
         *         of the player and resets the current level of the game.
         */
        void reincarnatePlayer();

        /** \fn void updateScreenState();
         * \brief Checks whether the player's score has passed the current high
         *         score and whether the player is still alive and updates the screen state.
         */
        void updateScreenState();

        /** \fn void updateMovingObjectsSound();
         * \brief Plays sound for spider and scorpion as they move.
         */
        void updateMovingObjectsSound();

        /** \fn void renderGameWonScreen();
         * \brief Displays the game won screen when the player has won the game.
         */
        void renderGameWonScreen();

        /** \fn void renderGameOverScreen();
         * \brief Displays the game over screen when the player has lost the game.
         */
        void renderGameOverScreen();

       /** \fn bool checkIFwindowOPen() const;
        * \brief check if the sfml window i open
       */
        bool checkIFwindowOPen() const;

        /** \fn void gameloop();
         * \brief Runs the game loop.
         */
        void gameloop();

        /** \fn void initializeGame();
         * \brief Generates Mushrooms and plays the game start sound.
         */
        void initializeGame();


    protected:

    private:
       gameStateClass currentGames_state;
       const ScreenParameters screen_parameters_{592, 640};
       presentationLayerClass presentationLayer_{screen_parameters_.getwidth(), screen_parameters_.getheight()};
       resourcesManagerClass resourcesManager_;
       gameEngineClass game_engine_{screen_parameters_};
       timerClass game_timer_;

};

#endif // DATALAYERCLASS_H
