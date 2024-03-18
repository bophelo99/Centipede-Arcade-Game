#ifndef CENTIPEDECLASS_H
#define CENTIPEDECLASS_H
/**
*/
#include "entityMovementBaseClass.h"
#include "ScreenParameters.h"
/**
*/
#include <algorithm>
#include <vector>
using std::vector;

/** \struct centipedeClassDemensions
 *	\brief Contains information about a centipedeClass's height, width and speed.
 *  \author 1932442 Bophilo Ntsemi and 1839578 Masilo Sekhele
 *  \version 3.0
 */
struct CentipedeDimension
{
    const float height = 14.0;
    const float width  = 14.0;
    const float speed  = 1.0;
    const float DownSlideSpeed = 16.0;
};

/** \enum  CentiBodyType
         *  \brief A strongly typed enum class representing the BodyType of the
         *  centipede.
         */
enum class CentiBodyType
{
    HEAD = 0,
    BODY
};

/** \class centipedeClass
 *  \brief This is a class that inherits from the IMovingEntity class. It
 *         contains virtual functions that will be overridden by centipedeClass class.
 *         It models a centipede segment's functionality in the game. The BodyType of a
 *         centipedeClass object can be changed. A centipedeClass object can move
 *         itself. If it is CentiBodyType::BODY, it stores where the head has had a collision
 *         and whether or not it was with a poisoned mushroom. Its movement checks if
 *         there are any head collisions and it changes direction if it is at a collision point.
 */
class centipedeClass: public entityMovementBaseClass
{
    public:
        /**\fn centipedeClass(const ScreenParameters& ScreenParameters_, CentiBodyType BodyType_, positionHandler position, objectsDirection direction);
         * \brief Parameterized Constructor. Creates a centipede segment object.
         *  \param ScreenParameters_ is of type ScreenParameters.
         *  \param BodyType_ is of type CentiBodyType enum class.
         *  \param position is of type positionHandler.
         *  \param cur_Direction is an eum of type objectsDirection enum class.
         */
        centipedeClass(const ScreenParameters& ScreenParameters_, CentiBodyType BodyType_, positionHandler position, objectsDirection direction);

        /** \fn virtual ~centipedeClass();
         * \brief Virtual Destructor. Destroys a CentipedeSegment object.
         */
        virtual ~centipedeClass();

        /** \fn virtual movingObjetsType getObjectType() const override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that returns
         *         a enum of movingObjetsType of a CentipedeSegment object.
         *  \return movingObjetsType an enum of the strongly typed enum class movingObjetsType.
         */
        virtual movingObjetsType getObjectType() const override;

        /** \fn virtual positionHandler getPosition() const override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that returns
         *         a centre position of the CentipedeClass object.
         *  \return positionHandler of the CentipedeClass object containing its current position.
         */
        virtual positionHandler getPosition() const override;

        /** \fn  virtual boundaryHandler getBoundary() override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that returns
         *         a entityMovementBaseClass Box indicating the rectangular area covered by a CentipedeClass object.
         *  \return entityMovementBaseClass Box object of the type entityMovementBaseClass.
         */
        virtual boundaryHandler getBoundary() override;

        /** \fn  virtual objectsDirection getDirection() const override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that
         *         returns the current direction of a Centipede object.
         *  \return objectsDirection an enum of the enum class objectsDirection.
         */
        virtual objectsDirection getDirection() const override;

        /** \fn objectsDirection getPastDirection() const;
         * \brief A function that returns the previous direction of an object.
         *  \return The direction of the object of type objectsDirection of the enum class.
         */
        objectsDirection getPastDirection() const;

        /** \fn  virtual void move() override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that moves a CentipedeSegment object.
         *         Checks for head collision points in order to change direction.
         *         Calls the respective function to performs the poisoned movement of a Centipede object.
         */
        virtual void move() override;

        /** \fn virtual void setDirection(objectsDirection direction) override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that sets
         *         the direction of a Centipede object.
         *  \param direction an enum of enum class objectsDirection.
         */
        virtual void setDirection(objectsDirection direction) override;

        /** \fn virtual void eliminated() override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that sets the Centipede
         *         object as not alive when killed.
         *  \return void
         */
        virtual void eliminated() override;

        /** \fn  virtual void poison() override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that will be
         *         used to poison a Centipede object by changing the poisoned status to true.
         */
        virtual void poison() override;

        /** \fn virtual void reincarnate() override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that will not
         *	       be implemented because Centipede objects have one life only.
         */
        virtual void reincarnate() override;

       /** \fn virtual bool isAlive() const override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that queries
         *        if a CentipedeSegment object is still alive or not.
         *  \return bool
         */
        virtual bool isAlive() const override;

       /** \fn virtual bool isPoisoned() const override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that will be
         *        used to return the poisoned status of the Centipede objects.
         *  \return bool stating whether the Centipede object is poisoned or not.
         */
        virtual bool isPoisoned() const override;

        /** \fn virtual int getLives() const override;
          * \brief Inherited from entityMovementBaseClass. A virtual function that
         *        gets a constant copy of the Centipede object's number of lives left.
         *  \return int containing the number of lives.
         */
        virtual int getLives() const override;

        /** \fn virtual int getPoints() const override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that will be
         *         used to return a Centipede object's hit points.
         *  \return int
         */
        virtual int getPoints() const override;

       /** \fn CentiBodyType getCentiBodyType() const;
         * \brief A function that returns the body type of the centipede segment.
         *  \return CentiBodyType an enum of type strongly typed enum class CentiBodyType.
         */
        CentiBodyType getCentiBodyType() const;

        /** \fn void switchDirection();
         * \brief A function that changes the direction of the object to Down, this
         *         is called when a collision is detected in front of an object.
         */
        void switchDirection();

        /** \fn void setCentiBodyType(CentiBodyType BodyType);
         * \brief A function that sets the body type of the centipede segment.
         *  \param BodyType is of type v of the enum class.
         */
        void setCentiBodyType(CentiBodyType BodyType);

        /** \fn float getAngulation() const;
         * \brief A function that returns the rotation angle of the centipede segment.
         *  \return float
         */
        float getAngulation() const;

       /** \fn void remove_if_HeadCollisions();
         * \brief A function that clears the vector of positions where the head of centipede
         *        train had a collision.
         */
        void remove_if_HeadCollisions();

        /** \fn void store_collision(positionHandler position, bool headPosionedCollision);
         * \brief A function that saves positions where the head of centipede
         *         train had a collision.
         */
        void store_collision(positionHandler position, bool headPosionedCollision);

    protected:

    private:
         ScreenParameters Screen_Parameters_;
         positionHandler position_;
         CentiBodyType Centi_BodyType_;
         objectsDirection present_direction, past_direction;
         static struct CentipedeDimension centi_dimension;
         /**
         */
            bool ifPoisoned = false;
           bool ifAlive  = true;
    bool ifPoisonedMovement  = false;
    bool ifPoisonedChange;
    bool ifBottom;
         /**
         */
         int CountDown; float angulation = 0;
         vector<bool> IfPoisonedHeadCollisions;
         vector<positionHandler> HeadCollisions;

         /** \fn bool EntryMovement();
          * \brief Controls the movements of the centipede segment upon entry.
         */
         bool EntryMovement();

         /** \fn void moveRight();
          * \brief A function that increments x axis of the object's position.
         */
         void moveRight();

         /** \fn void moveLeft();
          * \brief A function that decrements x axis of the object's position.
         */
         void moveLeft();

         /** \fn void moveUp();
          * \brief A function that decrements y axis of the object's position.
         */
         void moveUp();

         /** \fn void moveDown();
          * \brief A function that increments y axis of the object's position.
         */
         void moveDown();

        /** \fn void if_HeadCollisions();
         * \brief Determines whether the CentipedeSegment has reached a position
         *  where the head collided. If it has the changeDirection() function is called.
         */
         void if_HeadCollisions();

         /** \fn void if_PoisonedMovement();
          * \brief Moves the centipede segment accordingly when it is poisoned.
         */
         void if_PoisonedMovement();

};

#endif // CENTIPEDECLASS_H
