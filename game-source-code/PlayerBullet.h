#ifndef PLAYERBULLET_H
#define PLAYERBULLET_H

#include "entityMovementBaseClass.h"
#include "ScreenParameters.h"

/** \struct PlayerBulletDimensions
 *	\brief Contains information about a PlayerBullet's height, width and speed.
 *  \author 1932442 Bophilo Ntsemi and 1839578 Masilo Sekhele
 *  \version 3.0
 */
struct PlayerBulletDimensions
{
    const float height = 12.0;
    const float width = 2.0;
    const float speed = 2.0;
};

/**  This is a class that inherits from the entityMovementBaseClass class. It models
 *  a Player's laser bullet object in the game. It contains virtual functions that
 *  will be overridden. A PlayerBullet moves upwards.
 *  \author 1932442 Bophilo Ntsemi and 1839578 Masilo Sekhele
 *  \version 3.0
 */

class PlayerBullet : public entityMovementBaseClass
{
    public:

        /** \fn PlayerBullet(positionHandler position, const ScreenParameters& grid);
         * \brief Parameterized Constructor. Creates a PlayerBullet object.
         *  \param position of type Position contains the centre position.
         *  \param grid is of type const Grid and contains the screen's width and height.
         */
        PlayerBullet(positionHandler position, const ScreenParameters& grid);

        /** \fn virtual ~PlayerBullet();
         * Virtual Destructor. Destroys a PlayerBullet object.
         */
        virtual ~PlayerBullet();

        /** \fn virtual void move() override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that
         *         moves a PlayerBullet object upwards.
         */
        virtual void move() override;

        /** \fn irtual objectsDirection getDirection() const override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that
         *         returns the direction of a PlayerBullet object.
         *  \return Direction an enum of type enum class Direction.
         */
        virtual objectsDirection getDirection() const override;

        /** \fn virtual void setDirection(objectsDirection direction) override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that sets
         *         the direction of a PlayerBullet object.
         *  \param direction an enum of enum class Direction.
         */
        virtual void setDirection(objectsDirection direction) override;

        /** \fn virtual movingObjetsType getObjectType() const override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that returns a
         *         enum ObjectType::PLAYER_LASER_BULLET of ObjectType of a PlayerBullet object.
         *  \return ObjectType an enum of the strongly typed enum class ObjectType.
         */
        virtual movingObjetsType getObjectType() const override;

        /** \fn virtual positionHandler getPosition() const override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that returns
         *         a Position of the PlayerBullet object.
         *  \return Position of the PlayerBullet object.
         */
        virtual positionHandler getPosition() const override;

        /** \fn virtual boundaryHandler getBoundary() override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that returns
		 *	       a BoundaryBox indicating the rectangular area covered by a PlayerBullet object.
         *  \return BoundaryBox object of the type boundaryHandler.
         */
        virtual boundaryHandler getBoundary() override;

        /** \fn virtual bool isAlive() const override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that queries
         *         if a PlayerBullet object is still alive or not.
         *  \return bool
         */
        virtual bool isAlive() const override;

        /** \fn virtual void eliminated() override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that sets the derived class
         *         object as not alive when killed.
         *  \return void
         */
        virtual void eliminated() override;

        /** \fn virtual void reincarnate() override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that can be
         *         used to bring PlayerBullet object back to life.
         *  \return void
         */
        virtual void reincarnate() override;

        /** \fn virtual int getLives() const override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that
         *         will be used to return the remaining lives of a PlayerBullet object.
         *  \return int indicating the number of remaining lives.
         */
        virtual int getLives() const override;

        /** \fn virtual bool isPoisoned() const override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that will be
         *         to return false for the poisoned status of a PlayerBullet object.
         *  \return bool
         */
        virtual bool isPoisoned() const override;

        /** \fn virtual void poison() override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that will not
         *         be implemented as a PlayerBullet cannot be poisoned.
         */
        virtual void poison() override;

        /**\fn virtual int getPoints() const override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that will be
         *         not be implemented as a PlayerBullet doesn't have hit points.
         *  \return int
         */
        virtual int getPoints() const override;

    private:
        positionHandler position_;
        const ScreenParameters grid_;
        objectsDirection direction_;
        static struct PlayerBulletDimensions dimensions_;
        bool alive_;
};

#endif // PLAYERBULLET_H
