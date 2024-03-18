#ifndef SCREENPARAMETERS_H
#define SCREENPARAMETERS_H

/** \class ScreenParameters
 *  \brief This class contains details about the screen such as the screen width
 *	       and height.
 *  \author 1932442 Bophilo Ntsemi and 1839578 Masilo Sekhele
 *  \version 3.0
 */
class ScreenParameters
{
    public:
        /** \fn ScreenParameters(unsigned int width = 592, unsigned int height = 640);
         * \brief Creates a screen grid object with of type ScreenParameters with default size 592x640.
         *  \param width is an unsigned int.
         *  \param height is an unsigned int.
         */
        ScreenParameters(unsigned int width = 592, unsigned int height = 640);

        /** \fn unsigned int getheight() const;
         * \brief Returns the Screen grid's width.
         *  \return unsigned int
         */
        unsigned int getheight() const;

        /** \fn unsigned int getwidth() const;
         * \brief Returns the Screen grid's height.
         *  \return unsigned int
         */
        unsigned int getwidth() const;

        /** \fn ~ScreenParameters();
         * \brief Default Destructor. Destroys a Grid object.
         */
        ~ScreenParameters();

    protected:

    private:
        /** //private variables
        */
        const unsigned int width_;
        const unsigned int height_;

};

#endif // SCREENPARAMETERS_H
