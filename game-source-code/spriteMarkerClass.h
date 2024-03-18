#ifndef SPRITEMARKERCLASS_H
#define SPRITEMARKERCLASS_H
/**
*/
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "movingObjetsType.h"
#include "objectsDirection.h"
/**
*/
/** \class spriteMarkerClass
 *  \brief A class that crops the texture to the correct image for game objects
 *  to be drawn on the screen. Some of the textures loaded contain more than one picture
 *  of an object in the image. This class is used to crop the texture to get the
 *  desired image in order to create animation of game objects presented on the screen.
 *  \author 1932442 Bophilo Ntsemi and 1839578 Masilo Sekhele
 *  \version 3.0
 */

class spriteMarkerClass
{
    public:
         /** \fn spriteMarkerClass(movingObjetsType objectType, objectsDirection direction, sf::Texture* ObjectTexture, unsigned int rows, const float time, sf::Vector2u image);
          *\brief Parameterized spriteMarkerClass constructor. Creates a SpriteSheet object.
         *
         * \param objectType is of type enum class movingObjetsType.
         * \param ObjectTexture is a pointer to an sf::Texture.
         * \param image is sf::Vector2u and contains the number of rows and columns in the texture.
         * \param time is a float that the the time delay between images.
         * \param rows is an unsigned int containing the row where the image can be located.
         * \param direction is of type enum class objectsDirection and contains the default
         *	      direction the game object faces in the texture.
         */
        spriteMarkerClass(movingObjetsType objectType, objectsDirection direction, sf::Texture* ObjectTexture, unsigned int rows, const float time, sf::Vector2u image);

        /**\fn movingObjetsType getObjectType() const;
         * \brief This function will return the object type.
         * \return objectType_ which is of enum class movingObjetsType.
         */
        movingObjetsType getObjectType() const;

        /**\fn sf::IntRect getTextureRect(objectsDirection Direction);
         * \brief This function will create a rect shape in the texture so that
         *        the correct image is taken from the sprite sheet. It takes in a direction
         *        and compares it with the default direction in the texture.
         * \param direction is of type movingObjetsType enum class.
         * \return sf::IntRect
         */
        sf::IntRect getTextureRect(objectsDirection Direction);

        /** \fn sf::IntRect getTextureRect(int column);
         *  \brief This function will create a rect shape in the texture using an
         *        sf::IntRect so that the correct image is taken from the spritesheet.
         *        It takes in a int that represents a column in the texture for those
         *        that have more than one image and are stationary objects.
         * \param column is an integer containing the column of interest in the texture.
         * \return sf::IntRect
         */
        sf::IntRect getTextureRect(int column);

        /** \fn void update(const float Dtime);
         * \brief Increments the image currently being looked at in the texture
         *        to animate movement.
         * \param Dtime is a const float that will be used to determine whether current
         *        image should be incremented after some delay.
         */
        void update(const float Dtime);

        /** \fn ~spriteMarkerClass();
         *  \brief Default Destructor. Destroys a SpriteSheet object.
         */
        ~spriteMarkerClass();

    protected:

    private:
        // Private variables:
        /**
        */
        movingObjetsType objectType_;
        objectsDirection direction_;
        float time_;
        float Tot_time_;
        unsigned int rows_;
        sf::Vector2u image_;
        sf::Vector2u PresentImage;
        sf::IntRect TexturRectAxis;

        // Private functions:
        /** \fn void createTextureRect(objectsDirection direction);
         *  \brief This function creates the sf::IntRect around the texture.
         *  \param direction is of type enum class objectsDirection. Contains the direction
         *         the game object is facing.
         */
        void createTextureRect(objectsDirection direction);
};
#endif // SPRITEMARKERCLASS_H
