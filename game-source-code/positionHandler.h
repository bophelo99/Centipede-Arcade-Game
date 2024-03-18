#ifndef POSITIONHANDLER_H
#define POSITIONHANDLER_H

/**	\class positionHandler
 *	\brief A class that contains an x and y value representing a screen position.
 *  \author 1932442 Bophilo Ntsemi and 1839578 Masilo Sekhele
 *  \version 3.0
 */
class positionHandler
{
    public:
        /** \fn positionHandler(float x=0.0f, float=0.0f);
         * \brief Parameterized Constructor. Creates a Position object with x and y coordinates.
         *         Default values are x=0 and y=0.
        */
       positionHandler(float x=0.0f, float=0.0f);

        /** \fn ~positionHandler();
         * \brief Default destructor. Destroys a Position object.
        */
        ~positionHandler();

       /** \fn positionHandler operator -(const positionHandler& rhs);
         * \brief Overloaded subtraction operator (-).
         * \return Position with the x and y results from the subtraction.
        */
        positionHandler operator -(const positionHandler& rhs);

       /** \fn bool operator==(const positionHandler& rhs) const;
        * \brief Overloaded equality operator (==).
        *  \return bool
        */
        bool operator==(const positionHandler& rhs) const;

        /** \fn float getX_position() const;
         * \brief Gets a constant copy of the current y coordinate of the object.
        * 	\return float with a constant copy of the y coordinate.
        */
        float getX_position() const;

        /** \fn float getY_position() const;
         * \brief Gets a constant copy of the current x coordinate of the object.
        * 	\return float with a constant copy of the x coordinate.
        */
        float getY_position() const;

        /** \fn void setXposition(float XPosition);
         * \brief Sets the x coordinate of an object.
        * 	\param XPosition is a float that defines x coordinate of an object.
        */
        void setXposition(float XPosition);

        /** \fn void setYposition(float YPosition);
         * \brief Sets the y coordinate of an object.
         * 	\param YPosition is a float that defines y coordinate of an object.
         */
        void setYposition(float YPosition);


    protected:

    private:
        float xPosition;
        float yPosition;

};
#endif // POSITIONHANDLER_H
