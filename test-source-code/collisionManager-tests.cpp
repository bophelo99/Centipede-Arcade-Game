#include "../game-source-code/collisionManagerClass.h"
#include "../game-source-code/mushroomsClass.h"
#include "../game-source-code/PlayerClass.h"
#include "../game-source-code/ScorpionClass.h"
#include "../game-source-code/Spider.h"

using std::make_shared;
using std::dynamic_pointer_cast;

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

// PLAYER BULLET COLLISIONS
TEST_CASE("Collision between PlayerBullet and Mushroom is detected")
{
    const ScreenParameters grid{592, 640};
    collisionManagerClass collision_handler{grid};
    struct MushroomDimensions dimensions_;
    struct PlayerBulletDimensions dimension_bullet;
    vector<entityBaseClass_ptr> game_objects;
    vector<entityMovementBaseClass_ptr> moving_game_objects;
    // Create mushrooms:
    auto mushroom1 = make_shared<mushroomsClass>(positionHandler{100, 100});
    game_objects.push_back(mushroom1);
    auto mushroom2 = make_shared<mushroomsClass>(positionHandler{100+dimensions_.width, 100});
    game_objects.push_back(mushroom2);

    auto bullet = make_shared<PlayerBullet>(positionHandler{100, 114}, grid);
    game_objects.push_back(bullet);
    moving_game_objects.push_back(bullet);

    auto moves_to_be_made = bullet->getPosition().getY_position();
    moves_to_be_made -= (mushroom1->getPosition().getY_position()+(dimensions_.width/2)-1);
    moves_to_be_made /= dimension_bullet.speed;

    for(auto moves_made = 0; moves_made<=moves_to_be_made; moves_made++)
    {
        bullet->move();
        collision_handler.detectEntitiesCollisions(game_objects, moving_game_objects);
    }

    CHECK(mushroom1->getLives()==3);
    CHECK(mushroom2->getLives()==4);
    CHECK(collision_handler.getPoints()==1);
    CHECK_FALSE(bullet->isAlive());
}

TEST_CASE("Collision between PlayerBullet and Centipede Head is detected and next Head is set")
{
    const ScreenParameters grid{592, 640};
    collisionManagerClass collision_handler{grid};
    struct CentipedeDimension  dimension_centipede;
    vector<entityBaseClass_ptr> game_objects;
    vector<entityMovementBaseClass_ptr> moving_game_objects;

    auto centipede_seg_ptr = make_shared<centipedeClass>(grid,CentiBodyType::HEAD,
                                      positionHandler{100,100}, objectsDirection::LEFT);

    game_objects.push_back(centipede_seg_ptr);
    moving_game_objects.push_back(centipede_seg_ptr);

    auto counter = 0.0f;
    while(game_objects.size() != 4)
    {
        counter +=(dimension_centipede.width+1);
        auto segment = make_shared<centipedeClass>(grid,CentiBodyType::BODY,
                                      positionHandler{100+counter,100}, objectsDirection::LEFT);

        game_objects.push_back(segment);
        moving_game_objects.push_back(segment);
    }//while

    // Create PlayerBullet at position near head to cause overlap:
    auto y_pos  = centipede_seg_ptr->getPosition().getY_position()+dimension_centipede.height-1;
    auto bullet = make_shared<PlayerBullet>(positionHandler{100,y_pos}, grid);
    game_objects.push_back(bullet);
    moving_game_objects.push_back(bullet);

    collision_handler.detectEntitiesCollisions(game_objects, moving_game_objects);
    CHECK_FALSE(game_objects.at(0)->isAlive());
    CHECK_FALSE(bullet->isAlive());

    centipede_seg_ptr = dynamic_pointer_cast<centipedeClass>(game_objects.at(1));
    CHECK(centipede_seg_ptr->getCentiBodyType()==CentiBodyType::HEAD);
}

TEST_CASE("Collision between PlayerBullet and Centipede Body is detected and next Head is set")
{
    const ScreenParameters grid{592, 640};
    collisionManagerClass collision_handler{grid};
    struct  CentipedeDimension  dimension_centipede;
    vector<entityBaseClass_ptr> game_objects;
    vector<entityMovementBaseClass_ptr> moving_game_objects;

    auto centipede_seg_ptr = make_shared<centipedeClass>(grid,CentiBodyType::HEAD,
                                      positionHandler{100,100}, objectsDirection::LEFT);

    game_objects.push_back(centipede_seg_ptr);
    moving_game_objects.push_back(centipede_seg_ptr);

    auto counter = 0.0f;
    while(game_objects.size() != 4)
    {
        counter +=(dimension_centipede.width+1);
        auto segment = make_shared<centipedeClass>(grid,CentiBodyType::BODY,
                                      positionHandler{100+counter,100}, objectsDirection::LEFT);

        game_objects.push_back(segment);
        moving_game_objects.push_back(segment);
    }//while

    // Create PlayerBullet at position near head to cause overlap:
    auto x_pos  = centipede_seg_ptr->getPosition().getX_position()+2.0f*(dimension_centipede.width+1);
    auto y_pos  = centipede_seg_ptr->getPosition().getY_position()+dimension_centipede.height-1;
    auto bullet = make_shared<PlayerBullet>(positionHandler{x_pos, y_pos}, grid);
    game_objects.push_back(bullet);
    moving_game_objects.push_back(bullet);

    collision_handler.detectEntitiesCollisions(game_objects, moving_game_objects);

    CHECK_FALSE(game_objects.at(2)->isAlive());
    CHECK_FALSE(bullet->isAlive());
    CHECK(collision_handler.getPoints()==100);

    centipede_seg_ptr = dynamic_pointer_cast<centipedeClass>(game_objects.at(3));
    CHECK(centipede_seg_ptr->getCentiBodyType()==CentiBodyType::HEAD);
}

TEST_CASE("Collision between PlayerBullet and Centipede Body is detected while multiple Centipede heads are in game objects vector")
{
    const ScreenParameters grid{592, 640};
    collisionManagerClass collision_handler{grid};
    struct CentipedeDimension dimension_centipede;
    vector<entityBaseClass_ptr> game_objects;
    vector<entityMovementBaseClass_ptr> moving_game_objects;

    auto centipede_seg_ptr = make_shared<centipedeClass>(grid,CentiBodyType::HEAD,
                                      positionHandler{100,100}, objectsDirection::LEFT);

    game_objects.push_back(centipede_seg_ptr);
    moving_game_objects.push_back(centipede_seg_ptr);

    auto counter = 0.0f;
    while(game_objects.size() != 5)
    {
        counter +=(dimension_centipede.width+1);
        auto segment = make_shared<centipedeClass>(grid,CentiBodyType::BODY,
                                      positionHandler{100+counter,100}, objectsDirection::LEFT);

        game_objects.push_back(segment);
        moving_game_objects.push_back(segment);
    }//while

    // Create PlayerBullet at position near head to cause overlap:
    auto x_pos  = centipede_seg_ptr->getPosition().getX_position()+4.0f*(dimension_centipede.width+1);
    auto y_pos  = centipede_seg_ptr->getPosition().getY_position()+dimension_centipede.height-1;
    auto bullet = make_shared<PlayerBullet>(positionHandler{x_pos, y_pos}, grid);
    game_objects.push_back(bullet);
    moving_game_objects.push_back(bullet);

    // HEAD 2
    centipede_seg_ptr = make_shared<centipedeClass>(grid,CentiBodyType::HEAD,
                                  positionHandler{100,300}, objectsDirection::RIGHT);
    game_objects.push_back(centipede_seg_ptr);
    moving_game_objects.push_back(centipede_seg_ptr);

    centipede_seg_ptr = make_shared<centipedeClass>(grid,CentiBodyType::BODY,
                                  positionHandler{85,300}, objectsDirection::RIGHT);

    game_objects.push_back(centipede_seg_ptr);
    moving_game_objects.push_back(centipede_seg_ptr);


    collision_handler.detectEntitiesCollisions(game_objects, moving_game_objects);
    CHECK_FALSE(game_objects.at(4)->isAlive());
    CHECK_FALSE(bullet->isAlive());
    CHECK(collision_handler.getPoints()==100);

    // Check that direction of last head is not changed.
    centipede_seg_ptr = dynamic_pointer_cast<centipedeClass>(game_objects.at(game_objects.size()-2));
    CHECK(centipede_seg_ptr->getCentiBodyType()==CentiBodyType::HEAD);
    CHECK(centipede_seg_ptr->getDirection()== objectsDirection::RIGHT);

    centipede_seg_ptr = dynamic_pointer_cast<centipedeClass>(game_objects.at(game_objects.size()-1));
    CHECK(centipede_seg_ptr->getCentiBodyType()==CentiBodyType::BODY);
    CHECK(centipede_seg_ptr->getDirection()== objectsDirection::RIGHT);
}

//
TEST_CASE("Collision between Centipede and Mushroom is detected")
{
    const ScreenParameters grid{592, 640};
    collisionManagerClass collision_handler{grid};
    struct CentipedeDimension dimension_centipede;
    struct MushroomDimensions  dimension_mushroom;
    vector<entityBaseClass_ptr> game_objects;
    vector<entityMovementBaseClass_ptr> moving_game_objects;

    auto x = 80.0f;
    auto y = 56.0f;
    auto centipede_seg_ptr = make_shared<centipedeClass>(grid,CentiBodyType::HEAD,
                                      positionHandler{x, y}, objectsDirection::LEFT);

    game_objects.push_back(centipede_seg_ptr);
    moving_game_objects.push_back(centipede_seg_ptr);

    auto counter = 0.0f;
    while(game_objects.size() != 5)
    {
        counter +=(dimension_centipede.width+1);
        auto segment = make_shared<centipedeClass>(grid,CentiBodyType::BODY,
                                      positionHandler{x+counter, y}, objectsDirection::LEFT);

        game_objects.push_back(segment);
        moving_game_objects.push_back(segment);
    }//while

    // Create Mushroom at position in direction of head to check collisions:
    auto mushroom = make_shared<mushroomsClass>(positionHandler{56.0f, y});
    game_objects.push_back(mushroom);

    auto centipede_tail_index = game_objects.size()-2;
    auto moves_to_be_made = game_objects.at(centipede_tail_index)->getPosition().getX_position();
    moves_to_be_made -= (dimension_centipede.width/2.0f);
    moves_to_be_made -= (mushroom->getPosition().getX_position()+dimension_mushroom.width/2.0f);
    moves_to_be_made /= dimension_centipede.speed;
    moves_to_be_made = static_cast<int>(moves_to_be_made);

    for(auto moves_made = 0; moves_made<=moves_to_be_made+1; moves_made++)
    {
        collision_handler.detectEntitiesCollisions(game_objects, moving_game_objects);
        // move
        for(auto& object : moving_game_objects)
            object->move();
    }//for

    CHECK(mushroom->isAlive());

    // Check if directions have changed:
    for(auto& object : moving_game_objects)
        CHECK(object->getDirection()==objectsDirection::RIGHT);

}

TEST_CASE("Collision between Centipede and poisoned Mushroom is detected")
{
    const  ScreenParameters grid{1920, 1080};
    collisionManagerClass collision_handler{grid};
    struct CentipedeDimension dimension_centipede;
    struct MushroomDimensions dimension_mushroom;
    vector<entityBaseClass_ptr> game_objects;
    vector<entityMovementBaseClass_ptr> moving_game_objects;

    auto x = 71.3f;
    auto y = 56.0f;
    auto centipede_head_ptr = make_shared<centipedeClass>(grid,CentiBodyType::HEAD,
                                      positionHandler{x, y}, objectsDirection::LEFT);

    game_objects.push_back(centipede_head_ptr);
    moving_game_objects.push_back(centipede_head_ptr);

    auto counter = 0.0f;
    while(game_objects.size() != 2)
    {
        counter +=(dimension_centipede.width+1);
        auto segment = make_shared<centipedeClass>(grid,CentiBodyType::BODY,
                                      positionHandler{x+counter, y}, objectsDirection::LEFT);

        game_objects.push_back(segment);
        moving_game_objects.push_back(segment);
    }//while
    auto centipede_tail_index = game_objects.size()-1;

    // Create poisoned Mushroom at position in direction of head to check collisions:
    auto mushroom = make_shared<mushroomsClass>(positionHandler{56.0f, y});
    mushroom->poison();
    game_objects.push_back(mushroom);

    auto moves_to_be_made = game_objects.at(centipede_tail_index)->getPosition().getX_position();
    moves_to_be_made -= (dimension_centipede.width/2.0f);
    moves_to_be_made -= (mushroom->getPosition().getX_position()+dimension_mushroom.width/2.0f);
    moves_to_be_made /= dimension_centipede.speed;
    moves_to_be_made = static_cast<int>(moves_to_be_made);

    for(auto moves_made = 0; moves_made<=moves_to_be_made+1; moves_made++)
    {
        collision_handler.detectEntitiesCollisions(game_objects, moving_game_objects);
        // move
        for(auto& object : moving_game_objects)
            object->move();
    }//for

    CHECK(mushroom->isAlive());
    CHECK(mushroom->isPoisoned());
    // Check if directions have changed:
    for(auto& object : moving_game_objects)
    {
        CHECK(object->isPoisoned());
    }

}

TEST_CASE("Centipede train follows head's collision with Mushroom even after Mushroom dies.")
{
    const ScreenParameters grid{592, 640};
    collisionManagerClass collision_handler{grid};
    struct CentipedeDimension dimension_centipede;
    struct MushroomDimensions dimension_mushroom;
    vector<entityBaseClass_ptr> game_objects;
    vector<entityMovementBaseClass_ptr> moving_game_objects;

    auto x = 400.0f;
    auto y = 56.0f;
    auto centipede_seg_ptr = make_shared<centipedeClass>(grid, CentiBodyType::HEAD,
                                      positionHandler{x, y}, objectsDirection::LEFT);

    game_objects.push_back(centipede_seg_ptr);
    moving_game_objects.push_back(centipede_seg_ptr);

    auto counter = 0.0f;
    while(game_objects.size() != 5)
    {
        counter +=(dimension_centipede.width+1);
        auto segment = make_shared<centipedeClass>(grid,CentiBodyType::BODY,
                                      positionHandler{x+counter, y}, objectsDirection::LEFT);

        game_objects.push_back(segment);
        moving_game_objects.push_back(segment);
    }//while
    auto centipede_tail_index = game_objects.size()-1;

    // Create Mushroom at position in direction of head to check collisions:
    auto mushroom = make_shared<mushroomsClass>(positionHandler{382.0f, y});
    game_objects.push_back(mushroom);

    auto moves_to_be_made = game_objects.at(centipede_tail_index)->getPosition().getX_position();
    moves_to_be_made -= (dimension_centipede.width/2.0f);
    moves_to_be_made -= (mushroom->getPosition().getX_position()+dimension_mushroom.width/2.0f);
    moves_to_be_made /= dimension_centipede.speed;

    for(auto moves_made = 0; moves_made<=moves_to_be_made+1; moves_made++)
    {
        collision_handler.detectEntitiesCollisions(game_objects, moving_game_objects);
        // move
        int half_way = moves_to_be_made/2.0f;
        if(moves_made == half_way)
        {
            for(auto i = 0; i<4; i++)
                mushroom->eliminated();
        }

        for(auto& object : moving_game_objects)
            object->move();
    }//for

    CHECK_FALSE(mushroom->isAlive());

    // Check if directions have changed:
    for(auto& object : moving_game_objects)
        CHECK(object->getDirection()==objectsDirection::RIGHT);

}


TEST_CASE("Collision between Centipede Heads is resolved correctly")
{
    const ScreenParameters grid{592, 640};
    collisionManagerClass collision_handler{grid};
    SplitAxis sat_algorithm{};
    struct CentipedeDimension dimension_centipede;
    vector<entityBaseClass_ptr> game_objects;
    vector<entityMovementBaseClass_ptr> moving_game_objects;

    auto x = 115.0f;
    auto y = 56.0f;
    auto centipede_head_1_ptr = make_shared<centipedeClass>(grid,CentiBodyType::HEAD,
                                      positionHandler{x, y}, objectsDirection::LEFT);

    game_objects.push_back(centipede_head_1_ptr);
    moving_game_objects.push_back(centipede_head_1_ptr);

    //
    x = 100.0f;
    auto centipede_head_2_ptr = make_shared<centipedeClass>(grid,CentiBodyType::HEAD,
                                      positionHandler{x, y}, objectsDirection::RIGHT);

    game_objects.push_back(centipede_head_2_ptr);
    moving_game_objects.push_back(centipede_head_2_ptr);

    auto moves_to_be_made = 2;

    for(auto moves_made = 0; moves_made<=moves_to_be_made+1; moves_made++)
    {
        collision_handler.detectEntitiesCollisions(game_objects, moving_game_objects);
        // move
        for(auto& object : moving_game_objects)
            object->move();
        if(moves_made == 0)
            CHECK(sat_algorithm.checkOverlap(centipede_head_1_ptr->getBoundary(),
                                             centipede_head_2_ptr->getBoundary()));
    }//for

    CHECK(centipede_head_1_ptr->getDirection() == objectsDirection::RIGHT);
    CHECK(centipede_head_2_ptr->getDirection() == objectsDirection::RIGHT);
}

TEST_CASE("Collision between Scorpion and Mushroom poisons the Mushroom")
{
    const ScreenParameters grid{592, 640};
    collisionManagerClass collision_handler{grid};
    SplitAxis sat_algorithm{};
    struct MushroomDimensions dimensions_mushroom;
    struct ScorpionDimensions dimensions_scorpion;
    vector<entityBaseClass_ptr> game_objects;
    vector<entityMovementBaseClass_ptr> moving_game_objects;

    auto x = grid.getwidth()/2.0f;

    auto scorpion = make_shared<Scorpion>(grid);
    auto mushroom = make_shared<mushroomsClass>(positionHandler(x, scorpion->getPosition().getY_position()));

    game_objects.push_back(mushroom);
    game_objects.push_back(scorpion);
    moving_game_objects.push_back(scorpion);

    //move the scorpion across the screen
    while(scorpion->isAlive())
    {
        collision_handler.detectEntitiesCollisions(game_objects, moving_game_objects);
        // move
        for(auto& object : moving_game_objects)
            object->move();
    }//for

    CHECK_FALSE(sat_algorithm.checkOverlap(mushroom->getBoundary(),scorpion->getBoundary()));
    CHECK(mushroom->isPoisoned());
}

TEST_CASE("Collision between Player and Mushroom is detected successfully and collision resolution is performed")
{
    const ScreenParameters grid{592, 640};
    collisionManagerClass collision_handler{grid};
    SplitAxis sat_algorithm{};
    struct MushroomDimensions dimensions_mushroom;
    struct PlayerDimension dimensions_player;
    vector<entityBaseClass_ptr> game_objects;
    vector<entityMovementBaseClass_ptr> moving_game_objects;

    auto player = make_shared<PlayerClass>(grid);
    player->setDirection(objectsDirection::RIGHT);
    game_objects.push_back(player);
    moving_game_objects.push_back(player);

    auto player_pos = player->getPosition();
    auto x = player_pos.getX_position()+(dimensions_mushroom.width)-dimensions_player.speed;
    auto y = player_pos.getY_position();
    auto mushroom = make_shared<mushroomsClass>(positionHandler{x, y});
    game_objects.push_back(mushroom);

    CHECK(sat_algorithm.checkOverlap(player->getBoundary(), mushroom->getBoundary()));
    // Resolve collision:
    collision_handler.detectEntitiesCollisions(game_objects, moving_game_objects);

    CHECK_FALSE(sat_algorithm.checkOverlap(player->getBoundary(), mushroom->getBoundary()));
    CHECK(player->getDirection()==objectsDirection::NONE);
}

TEST_CASE("Collision between Player and Centipede is detected successfully")
{
    const ScreenParameters grid{592, 640};
    collisionManagerClass collision_handler{grid};
    SplitAxis sat_algorithm{};
    struct CentipedeDimension dimensions_centipede_seg;
    struct PlayerDimension dimensions_player;
    vector<entityBaseClass_ptr> game_objects;
    vector<entityMovementBaseClass_ptr> moving_game_objects;

    auto player = make_shared<PlayerClass>(grid);
    player->setDirection(objectsDirection::RIGHT);
    auto player_lives = player->getLives();
    game_objects.push_back(player);
    moving_game_objects.push_back(player);

    auto player_pos = player->getPosition();
    auto x = player_pos.getX_position()+(dimensions_centipede_seg.width)-dimensions_player.speed;
    auto y = player_pos.getY_position();

    auto centipede_head = make_shared<centipedeClass>(grid,CentiBodyType::HEAD,
                                      positionHandler{x, y}, objectsDirection::LEFT);
    game_objects.push_back(centipede_head);
    moving_game_objects.push_back(centipede_head);

    CHECK(sat_algorithm.checkOverlap(player->getBoundary(), centipede_head->getBoundary()));

    //Check:
    collision_handler.detectEntitiesCollisions(game_objects, moving_game_objects);
    player_lives-=1;

    CHECK(player->ifGotHit());
    CHECK(player->isAlive());
    CHECK(player->getLives()==player_lives);
    CHECK_FALSE(centipede_head->isAlive());
}

TEST_CASE("Collision between Spider and Mushroom is detected successfully.")
{
    const ScreenParameters grid{592, 640};
    collisionManagerClass  collision_handler{grid};
    SplitAxis sat_algorithm{};
    struct MushroomDimensions dimensions_mushroom;
    struct SpiderDimensions  dimensions_spider;
    vector<entityBaseClass_ptr> game_objects;
    vector<entityMovementBaseClass_ptr> moving_game_objects;

    auto spider = make_shared<Spider>(grid);
    game_objects.push_back(spider);
    moving_game_objects.push_back(spider);

    auto spider_pos = spider->getPosition();
    auto x = grid.getwidth()/2.0f;
    auto y = 0.0f;

    //create a column of mushrooms
    for(auto i=30; i<40;i++)
    {
        auto y = i*16 +24.0f;
        auto mushroom = make_shared<mushroomsClass>(positionHandler{x, y});
        game_objects.push_back(mushroom);
    }

    // move the spider across the screen
    while(spider->isAlive())
    {
        collision_handler.detectEntitiesCollisions(game_objects, moving_game_objects);
        // move
        for(auto& object : moving_game_objects)
            object->move();
    }//for

   auto alive_objects = count_if(game_objects.begin(), game_objects.end(),
                                 [](const entityBaseClass_ptr& object)
                                 {
                                    return(object->isAlive());
                                 });

    CHECK_FALSE(game_objects.size() == alive_objects);
}

