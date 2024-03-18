#ifndef SPIDER_H
#define SPIDER_H

#include "ScreenParameters.h"
#include "entityMovementBaseClass.h"
#include "movingObjetsType.h"

/** \struct SpiderDimensions
 *	\brief Contains information about a Spider's height, width and speed.
 *  \author 1932442 Bophilo Ntsemi and 1839578 Masilo Sekhele
 *  \version 3.0
 */

struct SpiderDimensions
{
    const float height = 16.0;
    const float width = 30.0;
    const float speed = 0.8;
};

/** \class Spider
 *  \brief This is a class that inherits from the IMovingEntity class. It models
 *         a Spider object in the game. It contains virtual functions that
 *         will be overridden. A Spider object moves in a zig-zag movement. This was
 *         achieved by calculating slopes in a random range based on the Spider's current
 *         position and moving it along the generated line. A Spider objects sets itself
 *         to dead if it reaches the grid's left or right boundaries.
 */
class Spider : public entityMovementBaseClass
{
    public:
        /** \fn Spider(const ScreenParameters& Screen_Parameters_);
         * \brief Parameterized Constructor. Creates a Spider object.
         *  \param grid is of type Grid and contains screen width and height.
         */
        Spider(const ScreenParameters& Screen_Parameters_);

        /** \fn  virtual ~Spider();
         * \brief Virtual Destructor. Destroys a Spider object.
         */
        virtual ~Spider();

        /** \fn virtual movingObjetsType getObjectType() const override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that returns
         *         an enum of  movingObjetsType::SPIDER.
         *  \return ObjectType an enum of the strongly typed enum class ObjectType.
         */
        virtual movingObjetsType getObjectType() const override;

         /** \fn virtual positionHandler getPosition() const override;
          * \brief Inherited from entityMovementBaseClass. A virtual function that returns
         *          a Position of a Spider object.
         *  \return Position of a Spider object.
         */
        virtual positionHandler getPosition() const override;

        /** \fn virtual boundaryHandler getBoundary() override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that returns a
         *         boundaryHandler' type Box indicating the rectangular area covered by a Spider object.
         *  \return boundaryHandler box object of the type boundaryHandler.
         */
        virtual boundaryHandler getBoundary() override;

        /** \fn virtual objectsDirection getDirection() const override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that returns
         *         the direction of a Spider object.
         *  \return Direction an enum of type enum classobjectsDirection.
         */
        virtual objectsDirection getDirection() const override;

        /** \fn virtual void move() override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that moves
         *         a Spider object in a zig-zag movement.
         */
        virtual void move() override;

        /** \fn virtual void setDirection(objectsDirection direction) override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that sets the
         *         direction of a Spider object.
         *  \param direction an enum of enum class Direction.
         */
        virtual void setDirection(objectsDirection direction) override;

        /** \fn virtual void eliminated() override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that sets
         *         a Spider object as not alive when killed.
         *  \return void
         */
        virtual void eliminated() override;

        /**\fn virtual void poison() override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that will not
         *        be implemented because a Spider cannot be poisoned.
         */
        virtual void poison() override;

        /** \fn virtual void reincarnate() override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that will not
         *         be implemented because a Spider only has one life.
         *  \return void
         */
        virtual void reincarnate() override;

       /** \fn  virtual bool isAlive() const override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that queries
         *        if a Spider object is still alive or not.
         *  \return bool
         */
        virtual bool isAlive() const override;

        /** \fn virtual bool isPoisoned() const override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that will be
         *         to return false for the poisoned status of a Spider object.
         *  \return bool
         */
        virtual bool isPoisoned() const override;

        /** \fn virtual int getLives() const override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that
         *         will be used to return the remaining lives of a Spider object.
         *  \return int indicating the number of remaining lives.
         */
        virtual int getLives() const override;

        /** \fn virtual int getPoints() const override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that will be
         *         used to return a Spider object's hit points.
         *  \return int
         */
        virtual int getPoints() const override;

    private:
        /**
        */
        const ScreenParameters ScreenParameters_;;
        positionHandler position_;
        objectsDirection major_direction_;
        objectsDirection movementDirection_;
        bool isAlive_;
        bool turningPointAvailable_;
        double slope_;
        positionHandler turningPoint_;
        static struct SpiderDimensions dimensions_;

        /** \fn void moveUp();
         * \brief A function that modifies the position of the object such that the
         * 	object moves up.
         */
        void moveUp();

        /** \fn void moveDown();
         * \brief A function that modifies the position of the object such that the
         * 	object moves down.
         */
        void moveDown();

        /** \fn void CalculateSlope();
         * \brief Generates the next turning point and gets the slope of the line
         * 	to that point.
         */
        void CalculateSlope();
};

#endif // SPIDER_H
