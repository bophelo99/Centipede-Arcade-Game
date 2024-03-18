#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
/**
*/
#include "../game-source-code/centipedeClass.h"
#include "../game-source-code/ScreenParameters.h"
#include <vector>
#include <algorithm>
/**
*/
/**
  * The following tests test for the centipede class
  *
  */
TEST_CASE("Centipede at Initial correct Position")
{
    ScreenParameters screen{400, 600};
    centipedeClass centipede(screen, CentiBodyType::HEAD, positionHandler{200.0f, 580.0f}, objectsDirection::DOWN);
    CHECK(centipede.getPosition() == positionHandler{200.0f, 580.0f});
}

TEST_CASE("Centipede can move right, lest, up and down")
{
    ScreenParameters screen{400, 600};
    centipedeClass centipede(screen, CentiBodyType::HEAD, positionHandler{200.0f, 300.0f}, objectsDirection::DOWN);
    auto Xpos = centipede.getPosition().getX_position();
    auto Ypos = centipede.getPosition().getY_position();

    centipede.move();
    CentipedeDimension centi_dimension;
    Ypos +=centi_dimension.DownSlideSpeed;
    //check moved down
    CHECK(centipede.getPosition() == positionHandler{Xpos, Ypos});

    centipede.switchDirection();
    centipede.move();
    Ypos -=centi_dimension.DownSlideSpeed;
    //check moved up
    CHECK(centipede.getPosition() == positionHandler{Xpos, Ypos});

    centipede.setDirection(objectsDirection::LEFT);
    centipede.move();
    Xpos -= centi_dimension.speed;
    //check moved left
    CHECK(centipede.getPosition() == positionHandler{Xpos, Ypos});

    centipede.setDirection(objectsDirection::RIGHT);
    centipede.move();
    Xpos += centi_dimension.speed;
    //check moved right
    CHECK(centipede.getPosition() == positionHandler{Xpos, Ypos});
}

TEST_CASE("centipede turns when it collide with the right and left screen boundaries")
{
    //right boundary
    ScreenParameters screen{400,600};
    CentipedeDimension centi_dimension;
    centipedeClass centipede(screen, CentiBodyType::HEAD, positionHandler{400-(centi_dimension.width*0.5f),600}, objectsDirection::RIGHT);
    auto Xpos = centipede.getPosition().getX_position()-centi_dimension.speed;
    auto Ypos = centipede.getPosition().getY_position()-centi_dimension.DownSlideSpeed;

    centipede.move();
    ///check turned to left after colliding with right boundary
    CHECK(centipede.getDirection() == objectsDirection::LEFT);
    CHECK(centipede.getPosition() == positionHandler{Xpos, Ypos});

    //left boundary
    centipedeClass  centipede1(screen, CentiBodyType::HEAD, positionHandler{(centi_dimension.width*0.5f),300.0f}, objectsDirection::LEFT);
    Xpos = centipede.getPosition().getX_position()+centi_dimension.speed;
    Ypos = centipede.getPosition().getY_position()-centi_dimension.DownSlideSpeed;

    centipede1.move();
   // centipede1.move();
    ///check turned to left after colliding with right boundary
    CHECK(centipede1.getDirection() == objectsDirection::RIGHT);
    //CHECK(centipede1.getPosition() == positionHandler{Xpos, Ypos});
}
