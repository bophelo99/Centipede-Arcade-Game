#ifndef PRESENTATIONLAYERCLASS_H
#define PRESENTATIONLAYERCLASS_H
/**
*/
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/Music.hpp>
/**
*/
#include "splashScreenClass.h"
#include "entityBaseClass.h"
#include "entityMovementBaseClass.h"
#include "resourcesManagerClass.h"
#include "spriteMarkerClass.h"
#include "KeyboardInputKeys.h"
#include "centipedeClass.h"
#include "GameSounds.h"
#include "GameOverScreen.h"
#include "GameWonScreen.h"
/**
*/
#include <vector>
#include <memory>
#include <map>
#include <algorithm>
/**
*/
using std::vector;
using std::shared_ptr;
using std::map;
using std::pair;
using std::find_if;

/** \class presentationLayerClass
 *  \brief Uses the SFML Graphics Library to draw all game objects on the screen.
 *  \author 1932442 Bophilo Ntsemi and 1839578 Masilo Sekhele
 *  \version 3.0
 */
class presentationLayerClass
{
    public:
        /** \fn presentationLayerClass(const unsigned int screen_width, const unsigned int screen_height);
         * \brief Parametrized Constructor. Creates a Presentation object.
         *  \param screen_width is the width of the screen.
         *  \param screen_height is the height of the screen.
         */
        presentationLayerClass(const unsigned int screen_width, const unsigned int screen_height);

        /** \fn  void displaySplashScreen();
         * \brief Displays a Splashscreen at the beginning of the game.
         */
        void displaySplashScreen();

        /** \fn void loadResources(const vector<resourcesManagerClass>& resouceObject);
         * \brief Loads all the game's textures.
         *  \param resouceObject is a const vector of resourcesManagerClass passed by reference.
         */
        void loadResources(const vector<resourcesManagerClass>& resouceObject);

        /** \fn void displayGameObjects(const vector<shared_ptr<entityBaseClass>>& gameObjects, const int lives, const int score, const int highScore, tuple<const int, const int>levelInfo);
         *	\brief Draws all the game objects onto the screen. Including the player's
         *         score, lives and the game's highest score.
         * 	\param gameObjects is a const vector of shared pointers to entityBaseClass objects.
         * 	\param lives is an int and contains the player's remaining lives.
         * 	\param score is an int that has the player's current score.
         * 	\param highScore is an int that has the game's highest score.
         *  \param levelInfo is a  tuple<const int, const int> that indicates
         *         the current game level and max game level.
         */
        void displayGameObjects(const vector<shared_ptr<entityBaseClass>>& gameObjects, const int lives, const int score, const int highScore, tuple<const int, const int>levelInfo);

        /** \fn void ProccessEvents();
         * \brief Determines the keyboard keys pressed and acts accordingly.
         *         Polling is used by default.
         */
        void ProccessEvents();

        /** \fn void checkUpdatePressedKey(const bool ifKeyPressed, const sf::Keyboard::Key key);
         * \brief Checks which key was pressed/released and updates its status.
         *  \param key of type Key from the sf keyboard.
         *  \param ifKeyPressed is a bool stating if there is a key that is pressed.
         */
        void checkUpdatePressedKey(const bool ifKeyPressed, const sf::Keyboard::Key key);

        /**  \fn  bool ifWindowOpen() const;
         * \brief Returns a bool indicating whether the render window is open.
         *  \return bool window open status.
         */
        bool ifWindowOpen() const;

       /**\fn bool ifDownKeyPressed();
         * \brief Returns a bool indicating whether the DOWN arrow key was pressed.
         * \return bool indicating key status.
         */
        bool ifDownKeyPressed();

        /** \fn  bool ifUpKeyPressed();
         * \brief Returns a bool indicating whether the UP arrow key was pressed.
         *  \return bool indicating key status.
         */
        bool ifUpKeyPressed();

        /** \fn bool ifLeftKeyPressed();
         * \brief Returns a bool indicating whether the LEFT arrow key was pressed.
         *  \return bool indicating key status.
         */
        bool ifLeftKeyPressed();

        /** \fn  bool ifRightKeyPressed();
         * \brief Returns a bool indicating whether the RIGHT arrow key was pressed.
         *  \return bool indicating key status.
         */
        bool ifRightKeyPressed();

        /** \fn bool ifSpaceKeyPressed();
         * \brief Returns a bool indicating whether the SPACEBAR key was pressed.
         *  \return bool indicating key status.
         */
        bool ifSpaceKeyPressed();

        /** \fn void processGameObjectSound(movingObjetsType object_type);
         * \brief Updates the sound played when a Scorpion and Spider are moving.
         *         Also plays the sound used when a Mushroom is being regenerated.
         *  \param object_type is an enum of the strongly typed enum class movingObjetsType.
         */
        void processGameObjectSound(movingObjetsType object_type);

        /** \fn  void processPlayerShootSound();
         * \brief Plays the sound used to indicate that a player has shot a bullet.
         */
        void processPlayerShootSound();

        /** \fn void processLevelUpSound();
         * \brief Plays the sound used to indicate that a player levelled up.
         */
        void processLevelUpSound();

        /** \fn void drawGameWonScreen(const int player_score, const int high_score);
         * \brief Displays a Game Won Screen at the end of the game.
         *  \param player_score is an int and contains the player's score.
         *  \param high_score is an int and contains the game's high score.
         */
        void drawGameWonScreen(const int player_score, const int high_score);

        /** \fn  void drawGameOverScreen(const int player_score, const int high_score);
         * \brief Displays a Game Over Screen at the end of the game.
         *  \param player_score is an int and contains the player's score.
         *  \param high_score is an int and contains the game's high score.
         */
        void drawGameOverScreen(const int player_score, const int high_score);

        /**  \fn  void drawGameOverScreen(const int player_score, const int high_score);
         * \brief Default Destructor. Destroys a Presentation object.
         */

    protected:

    private:
        vector<spriteMarkerClass> spriteSheets;
        /**
        */
        sf::RenderWindow window_;
        sf::Font font;
        /**
        */
        splashScreenClass splas_screen;
        static struct KeyboardInputKeys KeyboardInputKey_;
        /**
        */
        map<GameSounds, shared_ptr<sf::Music>> gameSoundEffects;
        map<movingObjetsType, sf::Texture> gameTexture;

        /** \fn sf::Sprite makeSprite(const shared_ptr<entityBaseClass>& object);
         * \brief Returns a sf::Sprite with the necessary properties of the object given.
         *  \param object is a constant shared pointer to an entityBaseClass passed by reference.
         *  \return sf::Sprite sprite with properties of the object given.
         */
        sf::Sprite makeSprite(const shared_ptr<entityBaseClass>& object);

         /** \fn void animateObjects(float speed);
          * \brief Updates the animations of game objects that have more than one
         *          image to represent movement.
         * \param delta_time is a float that will have the time elapsed from the game loop.
         */
        void animateObjects(float speed);

         /** \fn sf::Sprite makeSpriteFromSpriteMarkerClass(const shared_ptr<entityBaseClass>& object);
          * \brief Returns a sprite with the correct animation for animated moving
         *          objects in the game.
         *  \param object is a constant shared pointer to an entityBaseClass passed by reference.
         *  \return sf::Sprite sprite with properties of the object given.
         */
        sf::Sprite makeSpriteFromSpriteMarkerClass(const shared_ptr<entityBaseClass>& object);

        /** \fn void  spriteSheet(const resourcesManagerClass& resource, const movingObjetsType& objectType);
         * \brief Populate SpriteSheet vector, spriteSheets,
         *         for the different game objects that have more than one image in a texture.
         *  \param resource is of type esourcesManagerClass which contains a game asset.
         * 	\param objectType is of type enum class movingObjetsType.
         */
        void  spriteSheet(const resourcesManagerClass& resource, const movingObjetsType& objectType);

        /** \fn  void  makeSpriteSheets(movingObjetsType objectType, objectsDirection direction, unsigned int rows, float time, sf::Vector2u image);
         * \brief Generates a SpriteSheet object and saves it into the vector
         *         spritesheets for the different game objects.
         * \param objectType is of type enum class movingObjetsType.
         * \param rows is an unsigned int indicating the row in the sprite sheet to use.
         * \param image is an sf::Vector2u and contains the number of columns and rows.
         * \param time is a float and is the time delay used between images for movement animation.
         * \param direction is the direction the sprite faces in the image loaded as a texture.
         */
        void  makeSpriteSheets(movingObjetsType objectType, objectsDirection direction, unsigned int rows, float time, sf::Vector2u image);

         /** \fn void displayLives(const int lives, const int score, const int highScore, tuple<const int, const int> gamelevelInfo);
          * \brief Displays the player's lives, current score, the high score and
         *         current and max game levels of the game on the render window.
         *  \param lives is an int representing the player's remaining lives.
         *  \param score is an int that has the player's current score.
         *  \param highScore is an int that has the game's highest score.
         *  \param gamelevelInfo is a  tuple<const int, const int> that indicates
         *         the current game level and max game level.
         */
        void displayLives(const int lives, const int score, const int highScore, tuple<const int, const int> gamelevelInfo);


};

#endif // PRESENTATIONLAYERCLASS_H
