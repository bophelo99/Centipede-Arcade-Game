#include "../game-source-code/gameEngineClass.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

TEST_CASE("Game initializes correctly.")
{
    ScreenParameters testGrid{592,640};
    gameEngineClass testGameEngine{testGrid};
    PlayerClass testPlayer{testGrid};
    HighScoreManager testHighScoreManager{};

    testGameEngine.makeMushrooms();
    auto[game_objects, player_lives, scores, game_level_info] = testGameEngine.getObjectParameters();
    auto[current_score, high_score] = scores;
    auto[current_level, max_level]  = game_level_info;

    CHECK_FALSE(game_objects.empty());
    CHECK(current_level == 1);
    CHECK(high_score    == testHighScoreManager.getHighScore());
    CHECK(current_score == 0);
    CHECK(player_lives  == testPlayer.getLives());
}

TEST_CASE("Moving Entities besides the Player are successfully created in the game.")
{
    ScreenParameters testGrid{592,640};
    gameEngineClass testGameEngine{testGrid};

    testGameEngine.makeMushrooms();
    testGameEngine.runGameEngine();
    auto moving_game_objects = testGameEngine.getMovingEntities();
    auto moving_entities = count_if(moving_game_objects.begin(),
                                    moving_game_objects.end(),
                                    [](const shared_ptr<entityMovementBaseClass>& object)
                                    {
                                        return(object->getObjectType() != movingObjetsType::PLAYER);
                                    });
    CHECK(moving_entities>0);
}

TEST_CASE("Player can be moved successfully based on keyboard input.")
{
    ScreenParameters testGrid{592,640};
    gameEngineClass testGameEngine{testGrid};
    PlayerClass testPlayer{testGrid};

    testGameEngine.runGameEngine();
    auto moving_game_objects = testGameEngine.getMovingEntities();
    auto iter_player = find_if( moving_game_objects.begin(),
                                moving_game_objects.end(),
                                [](const shared_ptr<entityMovementBaseClass>& object)
                                {
                                    return(object->getObjectType()==movingObjetsType::PLAYER);
                                });
    // Move left
    auto isLeftPressed  = true;
    auto isRightPressed = false;
    auto isUpPressed    = false;
    auto isDownPressed  = false;
    auto isSpacePressed = false;
    testGameEngine.IputKeysCommandsProcessing({isLeftPressed, isRightPressed, isUpPressed,
                                    isDownPressed, isSpacePressed});
    testGameEngine.runGameEngine();

    testPlayer.setDirection(objectsDirection::LEFT);
    testPlayer.move();

    CHECK(testPlayer.getPosition() == (*iter_player)->getPosition());
}

TEST_CASE("Moving entities besides the Player are successfully moved in the game.")
{
    ScreenParameters testGrid{592,640};
    gameEngineClass testGameEngine{testGrid};

    testGameEngine.makeMushrooms();
    testGameEngine.runGameEngine();
    auto moving_game_objects = testGameEngine.getMovingEntities();

    auto moving_game_enemies = vector<entityMovementBaseClass_ptr>(moving_game_objects.size()-1);
    copy_if( moving_game_objects.begin(), moving_game_objects.end(), moving_game_enemies.begin(),
             [](const shared_ptr<entityMovementBaseClass>& object)
             {
                return(object->getObjectType()!= movingObjetsType::PLAYER);
             });
    // Store current positions:
    vector<positionHandler> previousPositions;
    for(const auto& object : moving_game_enemies)
        previousPositions.push_back(object->getPosition());

    // move:
    testGameEngine.runGameEngine();
    auto index = 0;
    for(const auto& object : moving_game_enemies)
    {
        CHECK_FALSE(previousPositions.at(index) == object->getPosition());
    }
}

TEST_CASE("Player Bullet is fired when space pressed is true.")
{
    ScreenParameters testGrid{592,640};
    gameEngineClass testGameEngine{testGrid};

    testGameEngine.levelgameUp(); // Adds a delay
    testGameEngine.runGameEngine();
    auto isLeftPressed  = false;
    auto isRightPressed = false;
    auto isUpPressed    = false;
    auto isDownPressed  = false;
    auto isSpacePressed = true; //Shoot

    testGameEngine.IputKeysCommandsProcessing({isLeftPressed, isRightPressed, isUpPressed,
                                    isDownPressed, isSpacePressed});
    CHECK(testGameEngine.IfBulletFired());
}

