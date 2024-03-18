#include "gameEngineClass.h"
struct ActivityStates gameEngineClass::activityStates_;

gameEngineClass::gameEngineClass(const ScreenParameters& screen_parameters)
: ScreenParameters_{screen_parameters},
  mushroomManager_{screen_parameters},
  enemyEntities_{screen_parameters},
  collisionManager_{screen_parameters},
  timeSinceLastMushroomRegen{0}

{
   //ctor
   srand(time(0));
   playerObject = make_shared<PlayerClass>(ScreenParameters_);
   gameObjects.push_back(playerObject);
   movingameObjects.push_back(playerObject);
   HighScore = highScoreManager_.getHighScore();


}

gameEngineClass::~gameEngineClass()
{
    //dtor
}

void gameEngineClass::makeMushrooms()
{
 for(auto& mushroom_: mushroomManager_.makeMushrooms())
 {
   gameObjects.push_back(mushroom_);
 }
}

tuple<const vector<entityBaseClass_ptr>&, int, tuple<int, int>, tuple<int,int>> gameEngineClass::getObjectParameters()
{
  return {gameObjects, playerObject->getLives(), {ScoreDetails()},{LevelDetails()}};
}

std::tuple<int, int> gameEngineClass::ScoreDetails()
{
  return {playerObject->scoredetails(), HighScore};
}

std::tuple<int, int> gameEngineClass::LevelDetails()
{
  return {gameLevel, maxLevel};
}

void gameEngineClass::IputKeysCommandsProcessing(std::tuple<bool, bool, bool, bool, bool> KeyboardKey)
{
  auto [LeftKeyPressed,RightKeyPressed,UpKeyPressed,DownKeyPressed, SpaceKeyPressed] = KeyboardKey;
  if(LeftKeyPressed) playerObject->setDirection(objectsDirection::LEFT);
  else if(RightKeyPressed) playerObject->setDirection(objectsDirection::RIGHT);
  else if(UpKeyPressed) playerObject->setDirection(objectsDirection::UP);
  else if(DownKeyPressed) playerObject->setDirection(objectsDirection::DOWN);
  else playerObject->setDirection(objectsDirection::NONE);

  if(!activityStates_.isDebounceSpaceKey && SpaceKeyPressed)
  {
      activityStates_.isDebounceSpaceKey = true;
      auto Bullets = playerObject->shoot_bullet();

      for(auto& bullet: Bullets)
      {
          gameObjects.push_back(bullet);
          movingameObjects.push_back(bullet);
      }
      if(!Bullets.empty()) activityStates_.isBulletShot = true;
  }
activityStates_.isDebounceSpaceKey = SpaceKeyPressed;
}

void gameEngineClass::runGameEngine()
{
   generateEnemyEntities();
   UpdateMovementOfObjects();
   detectEntitiesCollisions();
   generateMushroom();
   SpawnFLeaMushrooms();
   updateScore();
   clearDeadENtities();
}

void gameEngineClass::detectEntitiesCollisions()
{
    collisionManager_.detectEntitiesCollisions(gameObjects, movingameObjects);
    playerObject->addscores(collisionManager_.getPoints());
}

void gameEngineClass::generateEnemyEntities()
 {
    auto CentipedeSegement = std::count_if(movingameObjects.begin(), movingameObjects.end(),[](const entityMovementBaseClass_ptr& object)
                                      {
                                         return(object->getObjectType()==movingObjetsType::CENTIPEDE);
                                      });
    if(!(activityStates_.isResetLevel) && CentipedeSegement==0)
    {
     reset();
     auto reduceDelay = 3.0;
     enemyEntities_.setCentipedeHeadsReleaseTime(enemyEntities_.getSpiderReleaseTime()-reduceDelay);
     ++gameLevel; activityStates_.isGameLevelUP = true;
     clearMovingEntties();
    }
    if(gameLevel>1) { generateCentipedeHead(gameLevel); }
    generateCentipede();
    generateScorpion();
    generateSpider();
    generateFlea();
    activityStates_.isResetLevel = false;
    if(gameLevel>maxLevel) activityStates_.isAllGameLevelsCOompleted=true;
 }

void gameEngineClass::reset()
{
    activityStates_.isResetLevel = true;
    enemyEntities_.resetEntities();
}

void gameEngineClass::levelgameUp()
{
    timerClass levelTime;
    levelTime.Start();
    auto delayTime=2.0;
    auto ElapseTime = levelTime.GetProcessTime();
    delayTime +=ElapseTime;

    while(true)
    {
        if(ElapseTime>delayTime) break;
            levelTime.Pause();
            ElapseTime=levelTime.getPauseTime();
            levelTime.Resume();
    }
    activityStates_.isGameLevelUP=false;
}

void gameEngineClass::generateCentipede()
{
    for(auto& centipede: enemyEntities_.generateCentipede())
   {
      gameObjects.push_back(centipede); movingameObjects.push_back(centipede);
   }
}

void gameEngineClass::generateCentipedeHead(int MaxHeads)
{
   for(auto& heads: enemyEntities_.generateCentipedeHeads(MaxHeads))
   {
      gameObjects.push_back(heads); movingameObjects.push_back(heads);
   }
}

void gameEngineClass::UpdateMovementOfObjects()
{
   for(auto& moveObject: movingameObjects)
   {
       if(moveObject->isAlive())
       {
          moveObject->move();
       }
   }
}

bool gameEngineClass::IfBulletFired() const
{
  auto state = activityStates_.isBulletShot;
  return state;
}

bool gameEngineClass::reincarnateplayer()
{
   if(playerObject->ifGotHit() && playerObject->isAlive())
   {
       clearMovingEntties();
       playerObject->reincarnate();
       return true;
   }
   return false;
}

bool gameEngineClass::IfPlayerLevelledUP()
{
   return activityStates_.isGameLevelUP;
}

bool  gameEngineClass::allStagesComplete()
{
   return(gameLevel>maxLevel);
}

bool gameEngineClass::IfMushroomReincarnationComplete()
{
    auto iter_mushroom = gameObjects.begin();
    auto delay = 0.30;
    while(iter_mushroom!=gameObjects.end())
    {
        if(((*iter_mushroom)->getObjectType() == movingObjetsType::MUSHROOM
           && (*iter_mushroom)->getLives()<4)|| ((*iter_mushroom)->isPoisoned()))
        {
            mushroom_reincarnate_timer.Pause();
            auto time_elapsed = mushroom_reincarnate_timer.getPauseTime();
            if((time_elapsed-timeSinceLastMushroomRegen)>delay)
            {
                timeSinceLastMushroomRegen = time_elapsed;
                (*iter_mushroom)->reincarnate();
                mushroom_reincarnate_timer.Resume();
                timeSinceLastMushroomRegen = mushroom_reincarnate_timer.GetProcessTime();
                return true;
            }
        }
        else ++iter_mushroom;
    }
    return false;
}

std::tuple<bool, bool, bool>gameEngineClass::gameStatus()
{
    return {playerObject->isAlive(), playerObject->scoredetails()>highScoreManager_.getHighScore(), allStagesComplete()};
}

const std::vector<entityMovementBaseClass_ptr>& gameEngineClass::getMovingEntities()
{
  return movingameObjects;
}

void gameEngineClass::generateSpider()
{
    for(auto& spider : enemyEntities_.generateASpider())
    {
        gameObjects.push_back(spider);
        movingameObjects.push_back(spider);
    }
}

void gameEngineClass::generateFlea()
{
   for(auto& flea : enemyEntities_.generateAFlea())
    {
        gameObjects.push_back(flea);
        movingameObjects.push_back(flea);
    }
}

void gameEngineClass::generateMushroom()
{
   for(auto& object: gameObjects)
    {
        if(object->getObjectType() == movingObjetsType::CENTIPEDE)
            if(!object->isAlive()){
             gameObjects.push_back(mushroomManager_.makeMushroom(object->getPosition()));
            }
    }
}

void gameEngineClass::SpawnFLeaMushrooms()
{
    for(auto& object: gameObjects)
    {
        if(object->getObjectType() == movingObjetsType::FLEA)
        {
            if(object->isAlive() && static_cast<int>(object->getPosition().getY_position())%40 == 0 &&
               object->getPosition().getY_position()<512.0 &&
               mushroomManager_.checkIfMushroomCanBeSpawn(object->getPosition()))
                {
                  gameObjects.push_back(mushroomManager_.makeMushroom(object->getPosition()));
                }
            }
        }
}

void gameEngineClass::generateScorpion()
{
  for(auto& scorpion : enemyEntities_.generateAScorpion())
    {
        gameObjects.push_back(scorpion);
        movingameObjects.push_back(scorpion);
    }
}

void gameEngineClass::clearDeadENtities()
{
    container_erase_if(gameObjects,
    [](shared_ptr<entityBaseClass>& game_object)
    {
        return (!game_object->isAlive());
    });

    container_erase_if(movingameObjects,
    [](shared_ptr<entityMovementBaseClass>& game_object)
    {
        return (!game_object->isAlive());
    });
}

void gameEngineClass::clearMovingEntties()
{
   container_erase_if(gameObjects,
    [](shared_ptr<entityBaseClass>& game_object)
    {
        return (game_object->getObjectType() != movingObjetsType::PLAYER &&
                game_object->getObjectType() != movingObjetsType::MUSHROOM);
    });

    container_erase_if(movingameObjects,
    [](shared_ptr<entityMovementBaseClass>& game_object)
    {
        return (game_object->getObjectType() != movingObjetsType::PLAYER);
    });
}

void gameEngineClass::updateScore()
{
  if(playerObject->scoredetails()>highScoreManager_.getHighScore())
       highScoreManager_.setHighScore(playerObject->scoredetails());
}
