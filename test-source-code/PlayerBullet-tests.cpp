#include "../game-source-code/PlayerBullet.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

TEST_CASE("Bullet is created at the right position."){

    ScreenParameters testGrid{650,600};
    PlayerBullet testBullet{positionHandler{325.0f,580.0f}, testGrid};

    CHECK(testBullet.getPosition() == positionHandler{325.0f,580.0f});
}

TEST_CASE("Bullet can move"){

    ScreenParameters testGrid{650,600};
    PlayerBullet testBullet{positionHandler{325.0f,580.0f}, testGrid};
    struct PlayerBulletDimensions dimensions_bullet;
    auto x_pos = testBullet.getPosition().getX_position();
    auto y_pos = testBullet.getPosition().getY_position()-(2.0f*dimensions_bullet.speed);

    testBullet.move();
    testBullet.move();

    CHECK(x_pos == doctest::Approx(testBullet.getPosition().getX_position()));
    CHECK(y_pos == doctest::Approx(testBullet.getPosition().getY_position()));
}

TEST_CASE("Bullet is not alive outside the grid"){

    ScreenParameters testGrid{650,600};
    struct PlayerBulletDimensions dimensions;
    auto y = dimensions.height/2.0f;
    PlayerBullet testBullet{positionHandler{325.0f, y}, testGrid};

    testBullet.move();
    CHECK_FALSE(testBullet.isAlive());
}
