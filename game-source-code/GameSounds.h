#ifndef GAMESOUNDS_H
#define GAMESOUNDS_H

/** \enum GameSounds
		 *  \brief A strongly typed enum class representing the type of game sounds.
		 *  \author 1932442 Bophilo Ntsemi and 1839578 Masilo Sekhele
         *  \version 3.0
		 */

enum class GameSounds
{
    SHOOTING_SOUND=0,             /** the sound used for bullets fired.*/
    LEVEL_UP_SOUND,               /** the sound used for Levelling up.*/
    MUSHROOM_REGENARATED_SOUND,   /** the sound used for Mushroom regeneration.*/
    SCORPION_MOVING_SOUND,        /** the sound used for Scorpion movement.*/
    SPIDER_MOVING_SOUND,           /** the sound used for Spider movement.*/
    FLEA_MOVING_SOUND             /** the sound used for Flea movement.*/
};
#endif // GAMESOUNDS_H
