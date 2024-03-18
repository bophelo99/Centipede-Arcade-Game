#ifndef SCORPION_H
#define SCORPION_H

#include "entityMovementBaseClass.h"
#include "ScreenParameters.h"

/** \struct ScorpionDimensions
 *	\brief Contains information about a Scorpion's height, width and speed.
 *  \author 1932442 Bophilo Ntsemi and 1839578 Masilo Sekhele
 *  \version 3.0
 */
struct ScorpionDimensions
{
    const float height = 16.0;
    const float width = 32.0;
    const float speed = 0.4;

};

/** \class Scorpion
 *  \brief This is a class that inherits from the entityMovementBaseClass class. It models
 *  a Scorpion object in the game. It contains virtual functions that
 *  will be overridden. A Scorpion moves horizontally across the ScreenParameters. It sets
 *  itself to dead if it reaches the ScreenParameters's left or right boundaries.
 */

class Scorpion : public entityMovementBaseClass
{
    public:

        /** \fn Scorpion(const ScreenParameters& Screen_Parameters_);
         * \brief Parameterized Constructor. Creates a Scorpion object.
         *  \param ScreenParameters of type ScreenParameters.
         */
        Scorpion(const ScreenParameters& Screen_Parameters_);

        /** \fn virtual ~Scorpion();
         * Virtual Destructor. Destroys a Scorpion object.
         */
        virtual ~Scorpion();

        /**  \fn virtual void move() override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that
         *         moves a Scorpion object horizontally across the ScreenParameters.
         */
        virtual void move() override;

        /** \fn virtual objectsDirection getDirection() const override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that
         *         returns the direction of a Scorpion object.
         *  \return Direction an enum of type enum class objectsDirection.
         */
        virtual objectsDirection getDirection() const override;

        /** \fn virtual void setDirection(objectsDirection direction) override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that sets
         *         the direction of a Scorpion object.
         *  \param direction an enum of enum class objectsDirection.
         */
        virtual void setDirection(objectsDirection direction) override;

        /** \fn virtual movingObjetsType getObjectType() const override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that returns a
         *         enum objectsDirection::SCORPION of ObjectType of a Scorpion object.
         *  \return ObjectType an enum of the strongly typed enum class objectsDirection.
         */
        virtual movingObjetsType getObjectType() const override;

        /** \fn virtual positionHandler getPosition() const override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that returns
         *         a positionHandler of the Scorpion object.
         *  \return Position
         */
        virtual positionHandler getPosition() const override;

        /** \fn virtual boundaryHandler getBoundary() override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that returns
		 *	       a BoundaryBox indicating the rectangular area covered by a Scorpion object.
         *  \return BoundaryBox object of the type boundaryHandler.
         */
        virtual boundaryHandler getBoundary() override;

        /** \fn virtual bool isAlive() const override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that queries
         *         if a Scorpion object is still alive or not.
         *  \return bool
         */
        virtual bool isAlive() const override;

        /** \fn virtual void eliminated() override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that sets the Scorpion
         *         object as not alive when killed.
         *  \return void
         */
        virtual void eliminated() override;

        /** \fn virtual void reincarnate() override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that will not
         *         be implemented because a Scorpion has one life only.
         *  \return void
         */
        virtual void reincarnate() override;

        /** \fn virtual int getLives()const override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that
         *         will be used to return the remaining lives of a Scorpion object.
         *  \return int indicating the number of remaining lives.
         */
        virtual int getLives()const override;

        /** \fn virtual bool isPoisoned() const override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that will be
         *         used to return false for the poisoned status of a Scorpion object.
         *  \return bool
         */
        virtual bool isPoisoned() const override;

        /** \fn virtual void poison() override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that will not be
         *         be implemented because a Scorpion object cannot be poisoned.
         */
        virtual void poison() override;

        /** \fn virtual int getPoints() const override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that will be
         *         used to return a Scorpion object's hit points.
         */
        virtual int getPoints() const override;

    private:
         /** private variables
         */
        const ScreenParameters ScreenParameters_;
        positionHandler position_;
        objectsDirection direction_;
        static struct ScorpionDimensions dimensions_;
        bool isAlive_;

        /** \fn void moveLeft();
         * \brief A function that decrements x axis of the object's position
         *  such that the Scorpion object moves left.
         */
        void moveLeft();

        /** \fn void moveRight();
         * \brief A function that increments x axis of the object's position.
         *  such that Scorpion object moves right.
         */
        void moveRight();
};

#endif // SCOPION_H
