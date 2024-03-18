#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../game-source-code/ScreenParameters.h"
#include "../game-source-code/Weapon.h"
#include "../game-source-code/timerClass.h"

TEST_CASE("A Player Bullet is successfully generated at a position.")
{
    ScreenParameters screen{400, 600};
    Weapon testWeapon{};
    timerClass testStopWatch{};
    testStopWatch.Start();
    auto delay = 2.0*testWeapon.getReloadTime();

    //Add delay
    while(true)
   {
        testStopWatch.Pause();
        auto time_elapsed = testStopWatch.getPauseTime();
        if(time_elapsed>delay) break;
        testStopWatch.Resume();
    }

    auto bullet = testWeapon.fire(screen, positionHandler{325, 400});
    CHECK_FALSE(bullet.empty());
    CHECK(bullet.at(0)->getPosition() == positionHandler{325, 400});
}

TEST_CASE("A Player Bullet is not generated before reload time elapses.")
{
    ScreenParameters screen{400, 600};
    Weapon testWeapon{};
    timerClass testStopWatch{};
    testStopWatch.Start();

    auto delay = 0.1;

    //Add delay
    while(true)
    {
        testStopWatch.Pause();
        auto time_elapsed = testStopWatch.getPauseTime();
        if(time_elapsed>delay) break;
        testStopWatch.Resume();
    }

    auto bullet = testWeapon.fire(screen, positionHandler{325, 400});
    CHECK(bullet.empty());
}

TEST_CASE("Weapon can be upgraded.")
{
    ScreenParameters screen{400, 600};
    Weapon testWeapon{};
    auto reload_time = testWeapon.getReloadTime();
    testWeapon.upgradeWeapon();

    CHECK(testWeapon.getReloadTime() < reload_time);
}

