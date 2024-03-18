#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
/**
*/
#include "../game-source-code/mushroomsClass.h"
#include "../game-source-code/ScreenParameters.h"
#include <vector>
#include <algorithm>
/**
*/
/**
  * The following tests test for the centipede class
  *
  */
TEST_CASE("mushroom can be created")
{
    mushroomsClass mushroom(positionHandler(23.0f, 12.0f));
    CHECK(mushroom.getPosition()== positionHandler(23.0f, 12.0f));
}

TEST_CASE("mushoom ca be poisoned")
{
    mushroomsClass mushroom(positionHandler(23.0f, 12.0f));
    mushroom.poison();
    CHECK(mushroom.isPoisoned());
}

TEST_CASE("mushroom can be shot( ad life can be decremeneted after each shot)")
{
   mushroomsClass mushroom(positionHandler(23.0f, 12.0f));
   mushroom.eliminated();
   mushroom.eliminated();
   CHECK(mushroom.getLives() == 2);
}

TEST_CASE("mushroom can die if all lives are lost")
{
   mushroomsClass mushroom(positionHandler(23.0f, 12.0f));
   mushroom.eliminated();
   mushroom.eliminated();
   mushroom.eliminated();
   mushroom.eliminated();
   CHECK(mushroom.getLives() == 0);
   CHECK_FALSE(mushroom.isAlive());
}

TEST_CASE("mushroom can be reincarnated to gain full lifes")
{
   mushroomsClass mushroom(positionHandler(23.0f, 12.0f));
   mushroom.eliminated();
   mushroom.eliminated();
   mushroom.eliminated();
   mushroom.eliminated();
   CHECK_FALSE(mushroom.isAlive());

   mushroom.reincarnate();
   CHECK(mushroom.isAlive());
}
