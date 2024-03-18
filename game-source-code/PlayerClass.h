#ifndef PLAYERCLASS_H
#define PLAYERCLASS_H
/**
*/
#include "ScreenParameters.h"
#include "entityMovementBaseClass.h"
#include "Weapon.h"
/**
*/
#include <vector>
#include <memory>

/** \struct PlayerDimension
 *	\brief Contains information about a Player's height, width and speed.
 *  \author 1932442 Bophilo Ntsemi and 1839578 Masilo Sekhele
 *  \version 3.0
 */
struct PlayerDimension
{
    const float height = 16.0;
    const float width  = 16.0;
    const float speed  = 1.0;
};

/** \class PlayerClass
 *  \brief This is a Player Class that inherits from the entityMovementBaseClass class. It
 *  contains virtual functions that have been overridden. It models
 *	a Player object. A Player can move and can shoot bullets.
 *  \author 1932442 Bophilo Ntsemi and 1839578 Masilo Sekhele
 *  \version 3.0
 */
class PlayerClass : public entityMovementBaseClass
{
    public:
         /** \fn PlayerClass(const ScreenParameters& Screen_Parameters_);
         * \brief Parameterized constructor. Creates a Player object.
         *  \param grid is of type grid.
         */
        PlayerClass(const ScreenParameters& Screen_Parameters_);

        /** \fn virtual movingObjetsType getObjectType() const override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that
         *         returns a enum of movingObjetsType::PLAYER.
         *  \return An enum of the strongly typed enum classmovingObjetsType.
         */
        virtual movingObjetsType getObjectType() const override;

        /** \fn virtual positionHandler getPosition() const override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that
         *         returns a Position of the Player object.
         *  \return positionHandler of the Player object containing its current position.
         */
        virtual positionHandler getPosition() const override;

        /** \fn virtual boundaryHandler getBoundary() override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that
         *         returns a boundary box indicating the rectangular area covered by a
         *         Player object.
         *  \return BoundaryBox object of the type boundaryHandler.
         */
        virtual boundaryHandler getBoundary() override;

        /** \fn virtual objectsDirection getDirection() const override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that
         *         returns the direction of the Player.
         *  \return Direction of the Player of type Direction of the enum class.
         */
        virtual objectsDirection getDirection() const override;

        /** \fn virtual void move() override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that
         *         moves a Player object left, right, up or down in a 2D movement.
         */
        virtual void move() override;

        /** \fn virtual void setDirection(objectsDirection direction) override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that
         *         sets the direction of the Player.
         *  \param direction of type Direction of the enum class.
         */
        virtual void setDirection(objectsDirection direction) override;

        /** \fn virtual void eliminated() override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that
         *         sets the Player as not alive when killed.
         *  \return void
         */
        virtual void eliminated() override;

        /** \fn virtual void poison() override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that will not
         *         be implemented because a Player object cannot be poisoned.
         */
        virtual void poison() override;

        /** \fn virtual void reincarnate() override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that will be
         *         used to bring the Player object back to life, if the remaining lives
         *         are not zero.
         */
        virtual void reincarnate() override;

       /** \fn virtual bool isAlive() const override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that
         *        queries if a Player object is still alive or not.
         * \return bool
         */
        virtual bool isAlive() const override;

        /** \fn virtual bool isPoisoned() const override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that will be
         *         to return false for the poisoned status of a Player object.
         *  \return bool
         */
        virtual bool isPoisoned() const override;

        /** \fn virtual int getLives() const override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that
         *         gets a constant copy of the Player object's number of lives left.
         *  \return int indicating the player's remaining lives.
         */
        virtual int getLives() const override;

        /** \fn virtual int getPoints() const override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that will be
         *         not be implemented as a Player doesn't have hit points.
         *  \return int
         */
        virtual int getPoints() const override;

        /**  \fn int scoredetails() const;
         * \brief A function that creates a constant copy of the player's score
         *         and returns it.
         *  \return int
         */
        int scoredetails() const;

        /** \fn std::vector<std::shared_ptr<PlayerBullet>> shoot_bullet();
         * \brief Creates player bullets and returns them in a vector.
         *  \return vector<shared_ptr<PlayerBullet>>
         */
        std::vector<std::shared_ptr<PlayerBullet>> shoot_bullet();

        /** \fn void addscores(int scoreupdate);
         * \brief Adds the given score to the player's current score.
         *  \param score of type int.
         */
        void addscores(int scoreupdate);

        /** \fn void upgradeGunShot();
         * \brief Upgrades the Player's weapon.
         */
        void upgradeGunShot();

        /** \fn  bool ifGotHit();
         * \brief Returns true if the player has collided with a deadly enemy.
         */
        bool ifGotHit();

        /** \fn virtual ~PlayerClass();
         * \brief Virtual Destructor. Destroys a Player object.
		 */
        virtual ~PlayerClass();

    protected:

    private:
        int score, numberOFLives_;
        /**
        */
        const ScreenParameters ScreenParameters_;
        /**
        */
        positionHandler position; objectsDirection direction_; Weapon weapon_;
        /**
        */
        bool ifgotHit;
        /**
        */
        struct PlayerDimension dimension;

};

#endif // PLAYERCLASS_H
