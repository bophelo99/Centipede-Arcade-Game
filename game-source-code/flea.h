#ifndef FLEA_H
#define FLEA_H

#include "ScreenParameters.h"
#include "entityMovementBaseClass.h"

struct fleaDimensions
{
    const float height = 16.0;
    const float width = 16.0;
    const float speed = 0.5;
};

/** \class FLea
 *  \brief This is a Interface Class that inherits from the entityMovementBaseClass class. It
 *          contains pure virtual functions that will be overridden by derived classes. It models a Flea that will move down from top of the
 *          game screen. the Flea alo spwans mushrooms as it descends
 *  \author 1932442 Bophilo Ntsemi and 1839578 Masilo Sekhele
 *  \version 3.0
 */
class flea: public entityMovementBaseClass
{
    public:
        /** \fn flea(const ScreenParameters& Screen_Parameters_);
         * \brief Parameterized Constructor. Creates a flea object.
         *  \param ScreenParameters of type ScreenParameters.
         */
        flea(const ScreenParameters& Screen_Parameters_);

        /** \fn virtual movingObjetsType getObjectType() const override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that returns
         *         an enum of  movingObjetsType::FLEA.
         *  \return movingObjetsType an enum of the strongly typed enum class movingObjetsType.
         */
        virtual movingObjetsType getObjectType() const override;

        /** \fn virtual positionHandler getPosition() const override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that returns
         *          a Position of a Flea object.
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
         *         the direction of a Flea object.
         *  \return Direction an enum of type enum class objectsDirection.
         */
        virtual objectsDirection getDirection() const override;

       /** \fn virtual void move() override;
         * \brief A pure virtual function that moves derived class objects.
         */
        virtual void move() override;

        /** \fn virtual void setDirection(objectsDirection direction) override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that sets the
         *         direction of a Flea object.
         *  \param direction an enum of enum class Direction.
         */
        virtual void setDirection(objectsDirection direction) override;

        /** \fn virtual void eliminated() override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that sets
         *         a Flea object as not alive when killed.
         *  \return void
         */
        virtual void eliminated() override;

        /** \fn virtual void poison() override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that will not
         *         be implemented because a Spider cannot be poisoned.
         */
        virtual void poison() override;

        /** \fn virtual void reincarnate() override;
         * \brief Inherited from entityMovementBaseClass. A pure virtual function that will be
         *         used to bring derived class objects back to life.
         *  \return void
         */
        virtual void reincarnate() override;

        /** \fn virtual bool isAlive() const override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that queries
         *         if a Flea object is still alive or not.
         *  \return bool
         */
        virtual bool isAlive() const override;

        /** \fn virtual bool isPoisoned() const override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that will be
         *         to return false for the poisoned status of a Flea object.
         *  \return bool
         */
        virtual bool isPoisoned() const override;

        /** \fn virtual int getLives() const override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that
         *         will be used to return the remaining lives of a Flea object.
         *  \return int indicating the number of remaining lives.
         */
        virtual int getLives() const override;

        /** \fn virtual int getPoints() const override;
         * \brief Inherited from entityMovementBaseClass. A virtual function that will be
         *         used to return a Flea object's hit points.
         *  \return int
         */
        virtual int getPoints() const override;

        /** \fn virtual ~flea();
         * \brief Virtual Destructor. Destroys a flea object.
         */
        virtual ~flea();

    protected:

    private:
        const ScreenParameters ScreenParameters_;
        bool poisoned, isAlive_;
        int numberOfLives;
        positionHandler position_;
        objectsDirection direction_;
        static struct fleaDimensions dimensions_;

        /** \fn void moveDown();
         * \brief A function that modifies the position of the object such that the
         * 	object moves down.
         */
        void moveDown();

        /** \fn  void looseLive();
         * \brief Decrements the lives of the mushroom.
         */
        void looseLive();

};
#endif // ACTIVITYSTATES_H
