#include "Weapon.h"

Weapon::Weapon():
        reload_time_{0.15},
        isWeaponUpgraded_{false}
{
    reload_timer_.Start();
    timeSinceLastShoot_ = reload_timer_.GetProcessTime();
}

vector<shared_ptr<PlayerBullet>> Weapon::fire(const ScreenParameters& grid, positionHandler start_position)
{
    vector<shared_ptr<PlayerBullet>> bullets;
    reload_timer_.Pause();
    auto time_elapsed = reload_timer_.getPauseTime();
    if((time_elapsed-timeSinceLastShoot_)>reload_time_)
    {
        bullets.push_back(std::make_shared<PlayerBullet>(start_position,grid));
        timeSinceLastShoot_ = time_elapsed;
    }
    reload_timer_.Resume();
    return bullets;
}

double Weapon::getReloadTime() const
{
    return reload_time_;
}

void Weapon::upgradeWeapon()
{
    if(!isWeaponUpgraded_) reload_time_/=2.0;

    isWeaponUpgraded_ = true;
}

void Weapon::reset()
{
    reload_time_        = 0.15;
    isWeaponUpgraded_   = false;
    timeSinceLastShoot_ = reload_timer_.GetProcessTime();
}


Weapon::~Weapon()
{
    //dtor
}
