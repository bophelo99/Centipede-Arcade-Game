#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
/**
*/
#include "../game-source-code/PlayerClass.h"
#include "../game-source-code/ScreenParameters.h"
#include "../game-source-code/timerClass.h"
#include <vector>
#include <algorithm>
/**
*/
/**
  * The following tests test for the Player class
  *
  */
TEST_CASE("IF The player at right Initial position at start")
{
    ScreenParameters screen{400, 600};
    PlayerClass player{screen};
    PlayerDimension player_dimension;
    float X_pos = 200, Y_pos = 600-player_dimension.height/2.0f;
    positionHandler player_position{X_pos, Y_pos};

    CHECK(player.getPosition() == player_position);
}

TEST_CASE("If Player movement boudary box is constructed")
{
    ScreenParameters screen{400, 600};
    PlayerClass player{screen};
    PlayerDimension player_dimension;
    auto X_pos = player.getPosition().getX_position();
    auto Y_pos = player.getPosition().getY_position();
    //
    auto X_PosWidthLimit = player_dimension.width*0.5f, Y_PosHeightLimit = player_dimension.height*0.5f;
    auto Vertex1X = X_pos-X_PosWidthLimit, Vertex1Y = Y_pos-Y_PosHeightLimit,
         Vertex2X = X_pos+X_PosWidthLimit, Vertex2Y = Y_pos-Y_PosHeightLimit,
         Vertex3X = X_pos-X_PosWidthLimit, Vertex3Y = Y_pos+Y_PosHeightLimit,
         Vertex4X = X_pos+X_PosWidthLimit, Vertex4Y = Y_pos+Y_PosHeightLimit;
    std::vector<positionHandler> BoundaryRect{positionHandler{Vertex1X, Vertex1Y},
                                              positionHandler{Vertex2X, Vertex2Y},
                                              positionHandler{Vertex3X, Vertex3Y},
                                              positionHandler{Vertex4X, Vertex4Y}};

     auto PlayerBoundaryVertices = player.getBoundary().getVertices();
     CHECK(PlayerBoundaryVertices[0] == BoundaryRect[0]);
     CHECK(PlayerBoundaryVertices[1] == BoundaryRect[1]);
     CHECK(PlayerBoundaryVertices[2] == BoundaryRect[2]);
     CHECK(PlayerBoundaryVertices[3] == BoundaryRect[3]);
}

TEST_CASE("Player can shoot Bullets"){

    ScreenParameters screen{400, 600};
    timerClass reloadTimer;
    PlayerClass player{screen};
    PlayerDimension player_dimension;
    auto X_pos = 325.0f, Y_pos = 600.0f-player_dimension.height*0.5f;
    positionHandler player_position{X_pos, Y_pos};

    auto bullets = player.shoot_bullet();
    while(true)
    {
        bullets = player.shoot_bullet();
        if(!bullets.empty()) break;
    }

    CHECK(!bullets.empty());
}

TEST_CASE("Player can be moved up")
{
     ScreenParameters screen{400, 600};
     PlayerClass player{screen};
     player.setDirection(objectsDirection::UP);
     player.move();

     PlayerDimension player_dimension;
     auto InitiaX_pos = screen.getwidth()*0.5f, InitialY_pos = screen.getheight() - player_dimension.height*0.5f;
     //move up
     auto NewY_pos = InitialY_pos+player_dimension.speed;
     positionHandler testPlayer_pos{InitiaX_pos, NewY_pos};

     CHECK(testPlayer_pos == player.getPosition());
}

TEST_CASE("Player can be moved down")
{
     ScreenParameters screen{400, 600};
     PlayerClass player{screen};
     player.setDirection(objectsDirection::DOWN);
     player.move();

     PlayerDimension player_dimension;
     auto InitiaX_pos = screen.getwidth()*0.5f, InitialY_pos = screen.getheight() - player_dimension.height*0.5f;
     //move down
     auto NewY_pos = InitialY_pos-player_dimension.speed;
     positionHandler testPlayer_pos{InitiaX_pos, NewY_pos};

     CHECK(testPlayer_pos == player.getPosition());
}

TEST_CASE("Player can be moved left")
{
     ScreenParameters screen{400, 600};
     PlayerClass player{screen};
     player.setDirection(objectsDirection::LEFT);
     player.move();

     PlayerDimension player_dimension;
     auto InitialX_pos = screen.getwidth()*0.5f, InitialY_pos = screen.getheight() - player_dimension.height*0.5f;
     //move left
     auto NewX_pos = InitialX_pos-player_dimension.speed;
     positionHandler testPlayer_pos{NewX_pos ,  InitialY_pos};

     CHECK(testPlayer_pos == player.getPosition());
}

TEST_CASE("Player can be moved right")
{
     ScreenParameters screen{400, 600};
     PlayerClass player{screen};
     player.setDirection(objectsDirection::RIGHT);
     player.move();

     PlayerDimension player_dimension;
     auto InitialX_pos = screen.getwidth()*0.5f, InitialY_pos = screen.getheight() - player_dimension.height*0.5f;
     //move left
     auto NewX_pos = InitialX_pos+player_dimension.speed;
     positionHandler testPlayer_pos{NewX_pos ,  InitialY_pos};

     CHECK(testPlayer_pos == player.getPosition());
}
