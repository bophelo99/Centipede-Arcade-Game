#ifndef ENTITYMOVEMENTBASECLASS_H
#define ENTITYMOVEMENTBASECLASS_H
/**
*/
#include "entityBaseClass.h"
#include "objectsDirection.h"
#include "boundaryHandler.h"
#include "positionHandler.h"
#include "movingObjetsType.h"


/** \class entityMovementBaseClass
 *  \brief This is a Interface Class that inherits from the IEntity class. It
 *         contains pure virtual functions that will be overridden by derived classes.
 *  \author 1932442 Bophilo Ntsemi and 1839578 Masilo Sekhele
 *  \version 3.0
 */
class entityMovementBaseClass: public entityBaseClass
{
    public:
        /** \fn entityMovementBaseClass(){};
         * \brief A pure virtual function that moves derived class objects.
         */
        entityMovementBaseClass(){};

        /** \fn virtual ~entityMovementBaseClass(){};
         * \brief A virtual destructor that destroys an IMovingEntity object.
         */
        virtual ~entityMovementBaseClass(){};

        /** \fn virtual movingObjetsType getObjectType() const = 0;
         * \brief Inherited from entityBaseClass. A pure virtual function that returns a enum of ObjectType of
         *         a derived class object.
         *  \return An enum of the strongly typed enum class ObjectType.
         */
        virtual movingObjetsType getObjectType() const = 0;

        /** \fn virtual positionHandler getPosition() const = 0;
         * \brief Inherited from entityBaseClass. A pure virtual function that returns a Position of the
         *  derived class object.
         *  \return Position of the derived class object containing its current position.
         */
        virtual positionHandler getPosition() const = 0;

        /** \fn virtual boundaryHandler getBoundary() = 0;
         * \brief Inherited from entityBaseClass. A pure virtual function that returns a v Box indicating
         *         the rectangular area covered by a derived class object.
         *  \return  boundaryHandler Box object of the type  boundaryHandler.
         */
        virtual boundaryHandler getBoundary() = 0;

        /** \fn virtual objectsDirection getDirection() const = 0;
         * \brief A pure virtual function that returns the direction of an object.
         *  \return Direction an enum of the enum class objectsDirection.
         */
        virtual objectsDirection getDirection() const = 0;

       /** \fn virtual void move() = 0;
         * \brief A pure virtual function that moves derived class objects.
         */
        virtual void move() = 0;

        /** \fn virtual void setDirection(objectsDirection direction) = 0;
         * \brief A pure virtual function that sets the direction of an object.
         *  \param direction an enum of enum class objectsDirection.
         */
        virtual void setDirection(objectsDirection direction) = 0;

        /** \fn virtual void eliminated() = 0;
          * \brief Inherited from  entityBaseClass. A pure virtual function that sets the derived class
         *         object as not alive when killed.
         *  \return void
         */
        virtual void eliminated() = 0;

        /** \fn virtual void poison() = 0;
         * \brief Inherited from entityBaseClass. A pure virtual function that will be
         *         used to poison a derived class object by changing the poisoned status to true.
         */
        virtual void poison() = 0;

        /** \fn virtual void reincarnate() = 0;
         * \brief Inherited from entityBaseClass. A pure virtual function that will be
         *  used to bring derived class objects back to life.
         *  \return void
         */
        virtual void reincarnate() = 0;

        /** \fn virtual bool isAlive() const = 0;
         * \brief Inherited from entityBaseClass. A pure virtual function that queries if a derived class object
         *         is still alive or not.
         *  \return bool
         */
        virtual bool isAlive() const = 0;

        /** \fn virtual bool isPoisoned() const = 0;
         * \brief Inherited from entityBaseClass. A pure virtual function that will be
         *         used to return the poisoned status of the derived class objects.
         *  \return bool stating whether the derived class object is poisoned or not.
         */
        virtual bool isPoisoned() const = 0;

        /** \fn virtual int getLives() const = 0;
         * \brief Inherited from entityBaseClass. A pure virtual function that
         *         will be used to return the remaining lives of a derived class object.
         *  \return int containing the number of remaining lives.
         */
        virtual int getLives() const = 0;

        /** \fn virtual int getPoints() const = 0;
         * \brief Inherited from entityBaseClass. A pure virtual function that will be
         *  used to return a derived class object's hit points.
         *  \return int
         */
        virtual int getPoints() const = 0;

    protected:

    private:
};

#endif // ENTITYMOVEMENTBASECLASS_H
