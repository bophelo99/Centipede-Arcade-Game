#ifndef GAMESTATECLASS_H
#define GAMESTATECLASS_H

/** \enum gameStateClass
 *  \brief A strongly typed enum class representing the different game
 *         screens that can be displayed.
 *  \author 1932442 Bophilo Ntsemi and 1839578 Masilo Sekhele
 *  \version 3.0
 */

enum class gameStateClass
{
   WELCOME_SPLASHSCREEN=0,  /** Represents the welcome SplashScreen.*/
   PLAY_GAME,               /** Represents the Game Active Screen.*/
   GAMEOVERSCREEN,          /** Represents the GameOverScreen.*/
   GAMEWONSCREEN            /** Represents the GameWonScreen.*/
};
#endif // GAMESTATECLASS_H
