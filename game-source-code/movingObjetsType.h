#ifndef MOVINGOBJETSTYPE_H
#define MOVINGOBJETSTYPE_H


/** \enum movingObjetsType
 *  \brief A strongly typed enum class representing the type of game objects.
 *  \author 1932442 Bophilo Ntsemi and 1839578 Masilo Sekhele
 *  \version 3.0
 */

enum class movingObjetsType
{
    PLAYER,        /** Represents a Player object.*/
    BULLET,        /** Represents a Player's lazer Bullet object.*/
    CENTIPEDE,     /** Represents a Centipede object.*/
    MUSHROOM,      /** Represents a Mushroom object.*/
    SCORPION,      /** Represents a Scorpion object.*/
    SPIDER,        /** Represents a Spider object.*/
    FLEA          /** Represents a Flea object.*/
};
#endif // MOVINGOBJETSTYPE_H
