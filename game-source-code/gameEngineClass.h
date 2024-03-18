#ifndef GAMEENGINECLASS_H
#define GAMEENGINECLASS_H
/**
*/
#include "collisionManagerClass.h"
#include "mushroomManager.h"
#include "PlayerClass.h"
#include "ACTIVITYSTATES.H"
#include "enemyEntities.h"
#include "Spider.h"
#include "timerClass.h"
#include "ScorpionClass.h"
#include "HighScoreManager.h"
#include "centipedeClass.h"
#include "flea.h"
/**
*/
#include <vector>
#include <memory>
#include <tuple>
#include <ctime>
#include <algorithm>
/**
*/
using std::tuple;
using std::vector;
using std::shared_ptr;
using std::make_shared;

/** \class gameEngineClass
 *  \brief This class has the responsibility of creating all the enemy objects
 *         of the game and the creation of Mushrooms. It also moves all the moving game
 *         objects. Queries keyboard input in order for the Player object to be moved
 *         and to be able to shoot PlayerBullet objects. It also performs the collision
 *         checks using a CollisionHandler class object. It is also responsible for
 *         reincarnating the Player and Mushrooms as well. It keeps track of the current
 *         game level. It also updates the high score. It also performs the logic needed
 *         to reset a level when the Player gets reincarnated.
 *  \author 1932442 Bophilo Ntsemi and 1839578 Masilo Sekhele
 *  \version 3.0
 */
class gameEngineClass
{
    public:
        /** \fn gameEngineClass(const ScreenParameters& screen_parameters);
         * \brief Parameterized constructor. Creates a GameEngine object.
         *  \param grid of type Grid.
         */
        gameEngineClass(const ScreenParameters& screen_parameters);

        /** \fn ~gameEngineClass();
         * \brief Destroys a GameEngine object.
         */
        ~gameEngineClass();

        /** \fn void makeMushrooms();
         * \brief Generates mushrooms at random positions.
         */
        void makeMushrooms();

        /** \fn void IputKeysCommandsProcessing(tuple<bool, bool, bool, bool, bool> KeyboardKey);
         * \brief Gets the input from keyboard.
         *  \param KeyboardKey is a tuple<bool, bool, bool, bool, bool>
         *         containing the key pressed bool for left, right, up, down, and space
         *         keys events.
         */
        void IputKeysCommandsProcessing(tuple<bool, bool, bool, bool, bool> KeyboardKey);

        /** \fn
         * \brief Moves all the game objects that can be moved.
         */
        void UpdateMovementOfObjects();

       /** \fn void runGameEngine();
         * \brief Calls the respective functions to create the game logic.
         */
        void runGameEngine();

        /** \fn void reset();
         * \brief Resets states of generated objects to false.
         */
        void reset();

        /** \fn void levelgameUp();
         * \brief Performs the level up logic.
         */
        void levelgameUp();

        /** \fn void generateEnemyEntities();
         * \brief Generates all the game moving enemy objects.
         */
        void generateEnemyEntities();

        /** \fn tuple<const vector<entityBaseClass_ptr>&, int, tuple<int, int>, tuple<int,int>> getObjectParameters();
          * \brief A function that returns the parameters needed for rendering.
         *         The parameters are the vector containing all the game objects, the
         *         player's remaining lives, the player's score, the game high score
         *         the current game level and the max game level.
         *  \return tuple<vector<entityBaseClass_ptr>&, int, int, tuple<int,int>>
         */
        tuple<const vector<entityBaseClass_ptr>&, int, tuple<int, int>, tuple<int,int>> getObjectParameters();

        /** \fn bool IfBulletFired() const;
          * \brief Returns true or false depending on whether the Player shot a
         *         bullet.
         *  \return bool
         */
        bool IfBulletFired() const;

        /** \fn bool reincarnateplayer();
         * \brief Reset the position of the player and generate a new Centipede train.
         *         Returns a bool indicating whether or not the Player was reincarnated.
         *  \return bool
         */
        bool reincarnateplayer();

        /** \fn bool IfPlayerLevelledUP();
         * \brief Returns a bool indicating whether the level has changed.
         *  \return bool
         */
        bool IfPlayerLevelledUP();

       /** \fn bool IfMushroomReincarnationComplete();
         * \brief Sets number of lives to max of Mushroom's that are not dead yet.
         *        Returns a bool if it successfully regenerated a Mushroom.
         *  \return bool
         */
        bool IfMushroomReincarnationComplete();

        /** \fn bool allStagesComplete();
         * \brief Queries if all the game stages have been completed.
         *  \return bool
         */
        bool allStagesComplete();

         /** \fn tuple<bool, bool, bool>gameStatus();
          * \brief Returns details about the player's alive status, whether the
         *          high score was passed, and whether all the levels have been completed.
         *  \return tuple<bool, bool, bool>
         */
        tuple<bool, bool, bool>gameStatus();

        /** \fn const vector<entityMovementBaseClass_ptr>& getMovingEntities();
         * \brief Returns the moving entities in the game.
         *  \return const vector<entityMovementBaseClass_ptr>&
         */
        const vector<entityMovementBaseClass_ptr>& getMovingEntities();

        /** \fn tuple<int, int> ScoreDetails();
         * \brief A function that returns the player's score and the high score.
         *  \return tuple<int, int>
         */
        tuple<int, int> ScoreDetails();

        /** \fn tuple<int, int>  LevelDetails();
         * \brief Returns the current game level and the max game level.
         *  \return tuple<int,int>
         */
        tuple<int, int>  LevelDetails();

    protected:

    private:
        const ScreenParameters ScreenParameters_;
        /**
        */
        vector<entityBaseClass_ptr> gameObjects;
        vector<entityMovementBaseClass_ptr> movingameObjects;
        /**
        */

        /**
        */
        mushroomManager mushroomManager_;
        static struct ActivityStates activityStates_;
        enemyEntities enemyEntities_;
        collisionManagerClass collisionManager_;
        timerClass mushroom_reincarnate_timer;
        HighScoreManager highScoreManager_;
        /**
        */
        shared_ptr <PlayerClass> playerObject;
        /**
        */
        int gameLevel =1, HighScore=0; const int maxLevel = 5;
        double timeSinceLastMushroomRegen;

        /** \fn void generateCentipede();
         * \brief Generates a Centipede made up of centipede segments.
         */
        void generateCentipede();

        /** \fn void generateCentipedeHead(int MaxHeads);
         * \brief Generates centipede heads.
         *  \param MaxHeads an int containing the number of heads to be generated.
         */
        void generateCentipedeHead(int MaxHeads);

        /** \fn void generateSpider();
         * \brief Generates a spider periodically.
         */
        void generateSpider();

        /** \fn void generateFlea();
         * \brief Generates a flea periodically.
         */
        void generateFlea();

        /** \fn void generateMushroom();
         * \brief Generates a mushrooms at a given position.
         */
        void generateMushroom();

        /** \fn void SpawnFLeaMushrooms();
         * \brief Generates a mushrooms at a Flea's path as it descends down the screen play.
         */
        void SpawnFLeaMushrooms();

        /** \fn void generateScorpion();
         * \brief Generates a scorpion at a random position.
         */
        void generateScorpion();

        /** \fn void detectEntitiesCollisions();
         * \brief Generates a spider periodically.
         */
        void detectEntitiesCollisions();

        /** \fn oid clearDeadENtities();
         * \brief Removes all dead entities from vector(s) where they exist.
         */
        void clearDeadENtities();

         /** \fn void clearMovingEntties();
          * \brief Removes all moving entities from vector(s) where they exist,
         *          excluding the player.
         */
        void clearMovingEntties();

        /** \fn void updateScore();
         * \brief Updates the game's high score.
         */
        void updateScore();

};


/**\brief  container_erase_if - a function that erases elements in a container based on a
 *         specified condition determined by the Predicate.
 *
 * \param container a std container passed by reference to be iterated through.
 * \param predicate can be a function that returns true or false.
 */
template<typename TypeContainer, typename PredicateT>
inline void container_erase_if(TypeContainer& container, const PredicateT& predicate)
{
    container.erase(remove_if(begin(container),
                              end(container), predicate),
                    end(container));
}

#endif // GAMEENGINECLASS_H
