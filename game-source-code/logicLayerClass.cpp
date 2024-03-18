#include "logicLayerClass.h"

logicLayerClass::logicLayerClass()
:currentGames_state{gameStateClass::WELCOME_SPLASHSCREEN}
{
    //ctor
    srand(time(0));
}

logicLayerClass::~logicLayerClass()
{
    //dtor
}

void logicLayerClass::gameloop()
{
  if( currentGames_state == gameStateClass::WELCOME_SPLASHSCREEN)
  {
    displayWelcomeSplashScreen();
  }
  setResourcesInfo();
  initializeGameObjects();
  game_timer_.Start();
  auto GameSpeed = 1.0f/600.0f; auto PreviousGameUpdateTime = 0.0;

  while(currentGames_state == gameStateClass::PLAY_GAME)
  {
     game_timer_.Stop();  PreviousGameUpdateTime +=game_timer_.getRunTime(); game_timer_.Start();
     while(PreviousGameUpdateTime>GameSpeed && currentGames_state == gameStateClass::PLAY_GAME)
     {
       if(checkIFwindowOPen()==false) return;
       PreviousGameUpdateTime -=GameSpeed;
       UpdateGamePlay();
     }
  }
   if(currentGames_state == gameStateClass::GAMEOVERSCREEN)
   {
       renderGameOverScreen();
   }
   if(currentGames_state == gameStateClass::GAMEWONSCREEN)
   {
       renderGameWonScreen();
   }
}

void logicLayerClass::initializeGame()
{
   setResourcesInfo();
   initializeGameObjects();
}


void logicLayerClass::setResourcesInfo()
{
   resourcesManager_.setResourceInfo();
   presentationLayer_.loadResources(resourcesManager_.ResoucesDirectoryPath());
}

void logicLayerClass::displayWelcomeSplashScreen()
{
   presentationLayer_.displaySplashScreen();
   currentGames_state = gameStateClass::PLAY_GAME;
}

gameStateClass logicLayerClass::getState()
{
   return currentGames_state;
}

void logicLayerClass::initializeGameObjects()
{
   game_engine_.makeMushrooms();
   displayGameObjects();
   game_engine_.reset();
}

void logicLayerClass::displayGameObjects()
{
   auto [gameObjects, lives, scoreInfo, levelInfo] = game_engine_.getObjectParameters();
   auto [score, highScore] = scoreInfo;
   presentationLayer_.displayGameObjects(gameObjects, lives, score, highScore, levelInfo);
}

void logicLayerClass::UpdateGamePlay()
{
    PocessInputkeys();
    levelUp();
    game_engine_.runGameEngine();
    reincarnatePlayer();
    displayGameObjects();
   // updateMovingObjectsSound();
    updateScreenState();
}

bool logicLayerClass::checkIFwindowOPen() const
{
    return presentationLayer_.ifWindowOpen();
}

void logicLayerClass::PocessInputkeys()
{
    presentationLayer_.ProccessEvents();
    auto leftKeyPressed = presentationLayer_.ifLeftKeyPressed(); auto rightKeyPressed = presentationLayer_.ifRightKeyPressed();
    auto upKeyPressed = presentationLayer_.ifUpKeyPressed(); auto downKeyPressed = presentationLayer_.ifDownKeyPressed();
    auto spaceKeyPressed = presentationLayer_.ifSpaceKeyPressed();
    game_engine_.IputKeysCommandsProcessing({leftKeyPressed, rightKeyPressed, upKeyPressed, downKeyPressed, spaceKeyPressed});

   /* if(game_engine_.IfBulletFired())
    {
        presentationLayer_.processPlayerShootSound();
    }*/
}

void logicLayerClass::levelUp()
{
    game_timer_.Pause();
    if(game_engine_.IfPlayerLevelledUP())
    {
         //presentationLayer_.processLevelUpSound();
         game_engine_.levelgameUp();
    }
    game_timer_.Resume();
}

void logicLayerClass::reincarnateMushrooms()
{
    game_timer_.Pause();
    while(true)
    {
        if(game_engine_.IfMushroomReincarnationComplete())
        {
           presentationLayer_.processGameObjectSound(movingObjetsType::MUSHROOM);
           displayGameObjects();
        }
        else break;
    }
    game_timer_.Resume();
}
void logicLayerClass::reincarnatePlayer()
{
 if(game_engine_.reincarnateplayer())
    {
        reincarnateMushrooms();
        game_engine_.reset();
    } else return;
}

void logicLayerClass::updateScreenState()
{
    auto[isPlayerAlive, highScorePassed, stagesComplete] = game_engine_.gameStatus();

    if(!isPlayerAlive)
        currentGames_state = gameStateClass::GAMEOVERSCREEN;
    else if((stagesComplete && isPlayerAlive) || (!isPlayerAlive && highScorePassed))
        currentGames_state = gameStateClass::GAMEWONSCREEN;
}

void logicLayerClass::updateMovingObjectsSound()
{
  for(const auto& object : game_engine_.getMovingEntities())
  presentationLayer_.processGameObjectSound(object->getObjectType());
}

void logicLayerClass::renderGameWonScreen()
{
    auto[score, high_score] = game_engine_.ScoreDetails();
    presentationLayer_.drawGameWonScreen(score, high_score);
}

void logicLayerClass::renderGameOverScreen()
{
    auto[score, high_score] = game_engine_.ScoreDetails();
    presentationLayer_.drawGameOverScreen(score, high_score);
}

