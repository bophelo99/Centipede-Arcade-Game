#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
/**
*/
#include "../game-source-code/HashGrid.h"
#include "../game-source-code/centipedeClass.h"
#include "../game-source-code/ScreenParameters.h"
/**
*/
/**
  * The following tests test for the Player class
  *
  */
TEST_CASE("Objects in same cell are found")
{
    ScreenParameters screen_{592, 640};
    auto increment = 0.0f;

    std::vector<entityBaseClass_ptr> game_Objects;
    while(game_Objects.size()!= 4)
    {
        game_Objects.push_back(std::make_shared<centipedeClass>(screen_, CentiBodyType::BODY, positionHandler{10+increment, 10+increment}, objectsDirection::RIGHT));
        increment+=10.0f;
    }

    HashGrid spatialGrid{screen_};
    spatialGrid.constructSpatialGrid(game_Objects);
    auto nearobjects = spatialGrid.DetectNearObjects(game_Objects.at(0));

    //verify 3 objects found
    CHECK(nearobjects.size() == 3);

    //check all objects found
    CHECK(nearobjects.at(0)==game_Objects.at(1));
    CHECK(nearobjects.at(1)==game_Objects.at(2));
    CHECK(nearobjects.at(2)==game_Objects.at(3));

}

TEST_CASE("object of not iterest cannot be found if other similar object are not availabe")
{
    ScreenParameters screen_{592, 640};
    auto increment = 0.0f;

    std::vector<entityBaseClass_ptr> game_Objects;
    while(game_Objects.size()!= 4)
    {
        game_Objects.push_back(std::make_shared<centipedeClass>(screen_, CentiBodyType::BODY, positionHandler{10+increment, 10+increment}, objectsDirection::RIGHT));
        increment+=90.0f;
    }

    HashGrid spatialGrid{screen_};
    spatialGrid.constructSpatialGrid(game_Objects);
    auto nearobjects = spatialGrid.DetectNearObjects(game_Objects.at(0));

    //verify 0 objects found
    CHECK(nearobjects.size() == 0);
}

TEST_CASE("objects in multiple cell are found if object of interest within boundary")
{
      ScreenParameters screen_{592, 640};
    auto increment = 0.0f;

    std::vector<entityBaseClass_ptr> game_Objects;

   //cell boundary
    game_Objects.push_back(std::make_shared<centipedeClass>(screen_, CentiBodyType::BODY, positionHandler{80, 80}, objectsDirection::RIGHT));

    //cell 0
    game_Objects.push_back(std::make_shared<centipedeClass>(screen_, CentiBodyType::BODY, positionHandler{20, 20}, objectsDirection::RIGHT));

    //cell 8
    game_Objects.push_back(std::make_shared<centipedeClass>(screen_, CentiBodyType::BODY, positionHandler{120, 40}, objectsDirection::RIGHT));

    //cell 9
    game_Objects.push_back(std::make_shared<centipedeClass>(screen_, CentiBodyType::BODY, positionHandler{120, 100}, objectsDirection::RIGHT));

    // cell 1
    game_Objects.push_back(std::make_shared<centipedeClass>(screen_, CentiBodyType::BODY, positionHandler{40, 120}, objectsDirection::RIGHT));
    HashGrid spatialGrid{screen_};
    spatialGrid.constructSpatialGrid(game_Objects);
    auto nearobjects = spatialGrid.DetectNearObjects(game_Objects.at(0));

    //verify 3 objects found
    CHECK(nearobjects.size() == 4);
}
