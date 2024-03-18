#ifndef ACTIVITYSTATES_H
#define ACTIVITYSTATES_H

/** \enum ActivityStates
 *  \brief A typed struct class representing the different game
 *         activities operation state that are occuring in the GameEngine.
 *  \author 1932442 Bophilo Ntsemi and 1839578 Masilo Sekhele
 *  \version 3.0
 */

struct ActivityStates
{
  bool isBulletShot = false;
  bool isDebounceSpaceKey = false;
  bool isAllGameLevelsCOompleted = false;
  bool isGameLevelUP= true;
  bool isResetLevel = true;
};
#endif // ACTIVITYSTATES_H
