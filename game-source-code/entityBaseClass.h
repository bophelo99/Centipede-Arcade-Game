#ifndef ENTITYBASECLASS_H
#define ENTITYBASECLASS_H
/**
*/
#include "movingObjetsType.h"
#include "boundaryHandler.h"
#include "POSITIONHANDLER.H"


/** \class  entityBaseClass
 *  \brief This is a Interface Class containing pure virtual functions that
 *  will be overridden by derived classes.
 *  \author 1932442 Bophilo Ntsemi and 1839578 Masilo Sekhele
 *  \version 3.0
 */
class entityBaseClass
{
    public:

        /**\fn virtual positionHandler getPosition() const = 0;
         * \brief A pure virtual function that returns a Position of the
         *         derived class object.
         *  \return positionHandler position of the derived class object containing its current positionHandler.
         */
        virtual positionHandler getPosition() const = 0;

        /** \fn virtual movingObjetsType getObjectType() const = 0;
         * \brief A pure virtual function that returns a enum of movingObjetsType of
         *         a derived class object.
         *  \return movingObjetsType enum of the strongly typed enum class movingObjetsType.
         */
        virtual movingObjetsType getObjectType() const = 0;

        /** \fn virtual boundaryHandler getBoundary() = 0;
         * \brief A pure virtual function that returns a boundaryHandler Box indicating
         *         the rectangular area covered by a derived class object.
         *  \return BoundaryBox object of the type boundaryHandler.
         */
        virtual boundaryHandler getBoundary() = 0;

        /** \fn virtual bool isAlive() const = 0;
         * \brief A pure virtual function that queries if a derived class object
         *         is still alive or not.
         *  \return bool
         */
        virtual bool isAlive() const = 0;

        /** \fn virtual bool isPoisoned() const = 0;
         * \brief A pure virtual function that will be used to return the poisoned
         *         status of the derived class objects.
         *  \return bool stating whether the derived class object is poisoned or not.
         */
        virtual bool isPoisoned() const = 0;

        /** \fn  virtual void eliminated() = 0;
         * \brief A pure virtual function that sets the derived class object as
         *         not alive when killed.
         *  \return void
         */
        virtual void eliminated() = 0;

        /** \fn virtual void reincarnate() = 0;
         * \brief A pure virtual function that will be used to bring a derived
         *         class object back to life.
         *  \return void
         */
        virtual void reincarnate() = 0;

        /** \fn virtual void poison() = 0;
         * \brief A pure virtual function that will be used to poison a
         *         derived class object by changing the poisoned status to true.
         */
        virtual void poison() = 0;

        /** \fn virtual int getLives() const = 0;
         * \brief A pure virtual function that will be used to return the remaining
         *         lives of a derived class object.
         *  \return int containing the number of remaining lives.
         */
        virtual int getLives() const = 0;

        /** \fn virtual int getPoints() const = 0;
         * \brief A pure virtual function that will be used to return a
         *         derived class object's hit points.
         *  \return int
         */
        virtual int getPoints() const = 0;

         /** \fn  virtual ~entityBaseClass(){};
         * \brief A virtual destructor that destroys an IEntity object.
         */
        virtual ~entityBaseClass(){};

    protected:

    private:
};

#endif // ENTITYBASECLASS_H
