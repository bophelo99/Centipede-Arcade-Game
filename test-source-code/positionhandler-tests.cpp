#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
/**
*/
#include "../game-source-code/positionHandler.h"
#include "../game-source-code/ScreenParameters.h"
#include <vector>
#include <algorithm>
/**
*/
/**
  * The following tests test for the positionHandler class
  *
  */
TEST_CASE("If Position of X and Y axis can be set and retrieved")
{
  positionHandler position{10.0f, 4.0f};
  auto Xpos = 10.0f, Ypos=4.0f;
  CHECK(position.getX_position() == Xpos);
  CHECK(position.getY_position() == Ypos);
}

TEST_CASE("position can be added")
{
    positionHandler position1{20.0f, 20.0f}, position2{10.0f, 5.0f};
    auto Xpos = 10.0f, Ypos = 15.0f;

    auto positionAdd = position1 - position2;
    CHECK(positionAdd.getX_position() == Xpos);
    CHECK(positionAdd.getY_position() == Ypos);
}

TEST_CASE("position can be checked for equality succssfully")
{
     positionHandler position1{10.0f, 15.0f};
     positionHandler position2{10.0f, 15.0f};

     CHECK(position1 ==  position2);
}
