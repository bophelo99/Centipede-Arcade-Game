#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
/**
*/
#include "../game-source-code/mushroomManager.h"
#include "../game-source-code/ScreenParameters.h"
#include <vector>
#include <algorithm>
/**
*/
/**
  * The following tests test for the Mushroom Manager class
  *
  */
TEST_CASE("Mushroom are created")
{
    ScreenParameters screen{400, 600};
    mushroomManager Mushrooms{screen};
    auto generateMushrooms = Mushrooms.makeMushrooms();
    CHECK(generateMushrooms.size() != 0);
}

TEST_CASE("mushrooms are created at random points in the screen")
{

}
