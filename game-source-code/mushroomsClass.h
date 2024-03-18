#ifndef MUSHROOMSCLASS_H
#define MUSHROOMSCLASS_H
/**
*/
#include "entityBaseClass.h"


/** \struct MushroomDimensions
 *	\brief Contains information about a Mushroom's height, and width.
 *  \author 1932442 Bophilo Ntsemi and 1839578 Masilo Sekhele
 *  \version 3.0
 */
struct MushroomDimensions
{
    const float height = 15.0;
    const float width = 16.0;

};

/** \class mushroomsClass
 *  \brief This is a class that defines a Mushroom object. It contains virtual functions
 *         inherited from IEntity that will be overridden. A Mushroom object has four lives, and
 *         it can be poisoned.
 *  \author 1932442 Bophilo Ntsemi and 1839578 Masilo Sekhele
 *  \version 3.0
 */
class mushroomsClass: public entityBaseClass
{
    public:

       /** \fn mushroomsClass(positionHandler position);
         * \brief Parameterized Constructor. Creates a mushroomsClass object.
         *  \param position the centre point where the Mushroom is located on the screen.
         */
        mushroomsClass(positionHandler position);

        /** \fn virtual ~mushroomsClass();
         * \brief Virtual Destructor. Destroys a Mushroom object.
         */
        virtual ~mushroomsClass();

        /** \fn virtual positionHandler getPosition() const override;
         * \brief Inherited from entityBaseClass. A virtual function that returns a Position of the
         *         Mushroom object.
         *  \return Position of the Mushroom object.
         */
        virtual positionHandler getPosition() const override;

        /** \fn virtual movingObjetsType getObjectType() const override;
         * \brief Inherited from movingObjetsType. A virtual function that returns a enum
         *         movingObjetsType::MUSHROOM of movingObjetsType of a object.
         *  \return movingObjetsType an enum of the strongly typed enum class movingObjetsType.
         */
        virtual movingObjetsType getObjectType() const override;

        /** \fn virtual boundaryHandler getBoundary() override;
         * \brief Inherited from movingObjetsType. A virtual function that returns a BoundaryBox indicating
         *         the rectangular area covered by the Mushroom object.
         *  \return boundaryHandler box object of the type boundaryHandler.
         */
        virtual boundaryHandler getBoundary() override;

        /** \fn virtual bool isAlive() const override;
         * \brief Inherited from movingObjetsType. A virtual function that queries if a Mushroom object
         *         is still alive or not.
         *  \return bool
         */
        virtual bool isAlive() const override;

        /** \fn virtual bool isPoisoned() const override;
         * \brief Inherited from movingObjetsType. A virtual function that will be used
         *         to return the poisoned status of a Mushroom object.
         *  \return bool stating whether the Mushroom object is poisoned or not.
         */
        virtual bool isPoisoned() const override;

        /** \fn virtual void eliminated() override;
         * \brief Inherited from movingObjetsType. A virtual function that sets the Mushroom
         *         object as not alive when killed.
         *  \return void
         */
        virtual void eliminated() override;

        /** \fn virtual void reincarnate() override;
         * \brief Inherited from movingObjetsType. A virtual function that will be used
         *         to set a Mushroom object's number lives to full.
         *  \return void
         */
        virtual void reincarnate() override;

        /** \fn virtual void poison() override;
         * \brief Inherited from movingObjetsType. A virtual function that will be used
         *         to poison a Mushroom object by changing the poisoned status to true.
         */
        virtual void poison() override;

        /** \fn virtual int getLives() const override;
         * \brief Inherited from movingObjetsType. A virtual function that will be used
         *         to return the remaining lives of a Mushroom object.
         *  \return int containing the number of remaining lives.
         */
        virtual int getLives() const override;

        /** \fn virtual int getPoints() const override;
         * \brief Inherited from movingObjetsType. A virtual function that will be
         *         used to return a Mushroom object's hit points.
         *  \return int
         */
        virtual int getPoints() const override;

    protected:

    private:
        /**
        */
        positionHandler position_;
        static struct MushroomDimensions dimensions_;
        /**
        */
        bool poisoned, Alive;
        /**
        */
        int numberOfLives;

        /** \brief Decrements the lives of the mushroom.
         */
        void looseLive();
};

#endif // MUSHROOMSCLASS_H
