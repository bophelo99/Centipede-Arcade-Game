#ifndef WEAPON_H
#define WEAPON_H


#include "timerClass.h"
#include "PlayerBullet.h"
#include "positionHandler.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::vector;

/**This is a class that models a weapon for the Player.
 *  It generates PlayerBullet objects at a Position passed in after a certain
 *  reload time has elapsed.
 *  \author 1932442 Bophilo Ntsemi and 1839578 Masilo Sekhele
 *  \version 3.0
 */

class Weapon
{
    public:
        /**  \fn  Weapon();
         *   \brief Default Constructor. Creates a Weapon object.
         */
        Weapon();

        /**\fn vector<shared_ptr<PlayerBullet>> fire(const ScreenParameters& grid, positionHandler start_position);
         * \brief Creates player bullet at the specified position and returns them in a vector.
         *  \param grid is of type Grid and is taken by reference.
         *  \param start_position is of type Position and is the staring point of the bullet.
         *  \return vector<shared_ptr<PlayerBullet>>
         */
        vector<shared_ptr<PlayerBullet>> fire(const ScreenParameters& grid, positionHandler start_position);

        /**\fn double getReloadTime() const;
         * \brief Returns the reload time of the weapon.
         */
        double getReloadTime() const;

        /**\fn void upgradeWeapon();
         * \brief Halves the reload time of the PlayerBullet.
         */
        void upgradeWeapon();

        /**\fn void reset();
         * \brief Resets the reload time to it default one.
         */
        void reset();

        /**\fn ~Weapon();
         * \brief Default Destructor. Destroys a Weapon object.
         */
        ~Weapon();

    private:
        timerClass reload_timer_;
        double timeSinceLastShoot_;
        double reload_time_;
        bool isWeaponUpgraded_;
};

#endif // WEAPON_H
