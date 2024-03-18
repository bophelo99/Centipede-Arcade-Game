#include "../game-source-code/Spider.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

TEST_CASE("Spider can be created at a random position in its allocated range")
{

    ScreenParameters testGrid{592,640};
    Spider testSpider(testGrid);
    struct SpiderDimensions dimensions;
    bool israndom = (testSpider.getPosition()==
                    positionHandler(testGrid.getwidth()-(dimensions.width/2.0f + 1.0f),
                             testGrid.getheight()- testGrid.getheight()*0.2f)) ||
                    (testSpider.getPosition()==
                    positionHandler(dimensions.width/2.0f + 1.0f),
                             testGrid.getheight()- testGrid.getheight()*0.2f);
    bool directionIsRandom = (testSpider.getDirection() == objectsDirection::LEFT) ||
                             (testSpider.getDirection() == objectsDirection::RIGHT);
    CHECK(israndom);
    CHECK(directionIsRandom);
}

TEST_CASE("Spider can move in a Direction"){

    ScreenParameters testGrid{592,640};
    Spider testSpider(testGrid);
    struct SpiderDimensions dimensions;
    auto initiaPos = testSpider.getPosition();
    testSpider.move();
    testSpider.move();
    CHECK_FALSE(testSpider.getPosition() == initiaPos);
}

TEST_CASE("Spider can be eliminated"){

    ScreenParameters testGrid{592,640};
    Spider testSpider(testGrid);
    struct SpiderDimensions dimensions;
    testSpider.eliminated();
    CHECK_FALSE(testSpider.isAlive());
}
