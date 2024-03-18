#include "../game-source-code/flea.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

TEST_CASE("Flea can be created at a random position horizontal position in its allocated range")
{

    ScreenParameters testGrid{592,640};
    flea testflea(testGrid);
    struct fleaDimensions dimensions;

    bool israndomPosition = (testflea.getPosition()==
                    positionHandler(testGrid.getwidth()-(dimensions.width/2.0f + 1.0f), 0));
    auto directionIsDown = objectsDirection::DOWN;

    CHECK_FALSE(israndomPosition);
    CHECK(directionIsDown==testflea.getDirection());
}

TEST_CASE("Flea only move in a Down Direction"){

    ScreenParameters testGrid{592,640};
    flea testflea(testGrid);
    struct fleaDimensions dimensions;

    auto newPosition = positionHandler(testflea.getPosition().getX_position(), 24);

    testflea.move();

    CHECK_FALSE(testflea.getPosition() == newPosition );
}

TEST_CASE("flea can be eliminated and has two lives"){

    ScreenParameters testGrid{592,640};
    flea testflea(testGrid);
    struct fleaDimensions dimensions;
// loose one life
    testflea.eliminated();
    CHECK(testflea.isAlive());
//loose both lives
    testflea.eliminated();
    CHECK_FALSE(testflea.isAlive());
}

