#include "presentationLayerClass.h"

struct KeyboardInputKeys presentationLayerClass::KeyboardInputKey_;

presentationLayerClass::presentationLayerClass(const unsigned int screen_width, const unsigned int screen_height)
:window_(sf::VideoMode(screen_width, screen_height), "CENTIPEDE", sf::Style::Close)
{
    ///ctor
}

void presentationLayerClass::displaySplashScreen()
{
   splas_screen.setplashScreenAssets(window_);
   splas_screen.drawplashScreen(window_);
}

void presentationLayerClass::drawGameWonScreen(const int player_score, const int high_score)
{
    GameWonScreen gameWonScreen;
    gameWonScreen.show(window_, player_score, high_score);
}

void presentationLayerClass::drawGameOverScreen(const int player_score, const int high_score)
{
    GameOverScreen gameOverScreen;
    gameOverScreen.show(window_, player_score, high_score);
}

void presentationLayerClass::processGameObjectSound(movingObjetsType object_type)
{
    auto temp_object_with_sound_start = static_cast<int>(movingObjetsType::MUSHROOM);
    auto temp_object = static_cast<int>(object_type);
    auto temp_mushroom_regen_sound =  static_cast<int>(GameSounds::MUSHROOM_REGENARATED_SOUND);
    if(temp_object>=temp_object_with_sound_start)
    {
        temp_object-=temp_object_with_sound_start;
        auto temp_sound = static_cast<GameSounds>(temp_object+temp_mushroom_regen_sound);
        auto iter_map = gameSoundEffects.find(temp_sound);
        if((iter_map->second)->getStatus()!=sf::Music::Playing)
        {
            (iter_map->second)->setVolume(10);
            (iter_map->second)->stop();
            (iter_map->second)->play();
        }
    }
}

void presentationLayerClass::processPlayerShootSound()
{
     auto iter_map = gameSoundEffects.find(GameSounds::SHOOTING_SOUND);
    (iter_map->second)->stop();
    (iter_map->second)->play();
}

void presentationLayerClass::processLevelUpSound()
{
     auto iter_map = gameSoundEffects.find(GameSounds::LEVEL_UP_SOUND);
    (iter_map->second)->stop();
    (iter_map->second)->play();
}

void presentationLayerClass::loadResources(const vector<resourcesManagerClass>& resouceObject)
{
   auto resouceObject_iterator = resouceObject.begin(); auto index=0;
   auto soundResourceObject_limit = std::find_if(resouceObject.begin(), resouceObject.end(),
                                    [](const resourcesManagerClass& resouce)
                                    { return (resouce.getresourceType() == resourcesManagerClass::defineTypeOfResource::PLAYER); });
   ///load Font
   font.loadFromFile(resouceObject_iterator->getresourceDirectoryPath());
   ///load sounds
   for(++resouceObject_iterator; resouceObject_iterator!=soundResourceObject_limit; ++resouceObject_iterator)
   {
     auto sound_pointer = std::make_shared<sf::Music>(); sound_pointer->openFromFile(resouceObject_iterator->getresourceDirectoryPath());
     sound_pointer->setVolume(10);
     auto holdSoundInfo = pair<GameSounds, shared_ptr<sf::Music>>(static_cast<GameSounds>(index++), sound_pointer);
     gameSoundEffects.insert(holdSoundInfo);
   }///for
   ///load Textures
   auto baseIndex = static_cast<int>(resourcesManagerClass::defineTypeOfResource::PLAYER);
   for(;resouceObject_iterator!=resouceObject.end(); ++resouceObject_iterator)
   {
     sf::Texture holdTexture; holdTexture.loadFromFile(resouceObject_iterator->getresourceDirectoryPath());
     if(resouceObject_iterator->getresourceType()!=resourcesManagerClass::defineTypeOfResource::BULLET &&
        resouceObject_iterator->getresourceType()!=resourcesManagerClass::defineTypeOfResource::SCORPION &&
        resouceObject_iterator->getresourceType()!=resourcesManagerClass::defineTypeOfResource::FLEA)
       holdTexture.setSmooth(true);
     auto currentIndex = static_cast<int>(resouceObject_iterator->getresourceType());
     auto TexturType = static_cast<movingObjetsType>(currentIndex-baseIndex);
     auto holdtextureInfo = std::pair<movingObjetsType, sf::Texture>(TexturType, holdTexture);
     gameTexture.insert(holdtextureInfo);

     ///generate spritesheet object for animated object
     spriteSheet(*resouceObject_iterator, TexturType);
   } ///for
}

void  presentationLayerClass::spriteSheet(const resourcesManagerClass& resource, const movingObjetsType& objectType)
{
     auto [resourceInfo, direction] = resource.getResourceInfo();
     if(resourceInfo.empty()) return;
     auto resourceRows=resourceInfo.at(0); auto resourcecolumns=resourceInfo.at(1);
     auto time=0.3f;
     for(auto row=0u; row<resourceRows; row++)
        makeSpriteSheets(objectType, direction, row, time, sf::Vector2u{resourcecolumns, resourceRows});
     ///for
     return;
}

void presentationLayerClass::makeSpriteSheets(movingObjetsType objectType, objectsDirection direction, unsigned int rows, float time, sf::Vector2u image)
{
   auto iterator = gameTexture.find(objectType);
   spriteMarkerClass sprite{objectType, direction, &(iterator->second), rows, time, image};
   spriteSheets.push_back(sprite);
  // spriteMarkerClass(movingObjetsType objectType, objectsDirection direction,
  // sf::Texture* ObjectTexture, unsigned int rows, const float time, sf::Vector2u image);
}

void presentationLayerClass::displayLives(const int lives, const int score, const int highScore, tuple<const int, const int> gamelevelInfo)
{
    sf::Sprite lives_sprite;
    lives_sprite.setColor(sf::Color::White);
    auto half = 2.0f;
    auto iter_map = gameTexture.find(movingObjetsType::PLAYER);
    lives_sprite.setTexture(iter_map->second);
    lives_sprite.setOrigin((iter_map->second).getSize().x/half, (iter_map->second).getSize().y/half);
    // Draw lives using a sprite and player texture:
    auto xPos = (iter_map->second).getSize().x;
    for(auto i=0; i<(lives-1); i++)
    {
        lives_sprite.setPosition(xPos, (iter_map->second).getSize().y/half);
        window_.draw(lives_sprite);
        xPos+=(iter_map->second).getSize().x;
    }
    // Draw levels
    auto [current_level, max_level] = gamelevelInfo;
    string level = "Level "+std::to_string(current_level)+" of "+std::to_string(max_level);
    sf::Text level_text(level, font);
    level_text.setCharacterSize(18);
    sf::FloatRect titleRect = level_text.getLocalBounds();
    level_text.setOrigin(titleRect.left + titleRect.width/half,
    titleRect.top  + titleRect.height/half);
    level_text.setFillColor(sf::Color::Green);
    xPos+=100.0f;
    level_text.setPosition(xPos, level_text.getCharacterSize()/half);

    // Draw Score and high score:
    sf::Text score_text(std::to_string(score), font);
    score_text.setCharacterSize(20);
    titleRect = score_text.getLocalBounds();
    score_text.setOrigin(titleRect.left + titleRect.width/half,
    titleRect.top  + titleRect.height/half);
    score_text.setFillColor(sf::Color::Magenta);

    score_text.setPosition(sf::Vector2f(window_.getSize().x/half,
                                        score_text.getCharacterSize()/half));

    sf::Text high_score_text(std::to_string(highScore), font);
    high_score_text.setCharacterSize(20);
    titleRect = high_score_text.getLocalBounds();
    high_score_text.setOrigin(titleRect.left + titleRect.width/half,
    titleRect.top  + titleRect.height/half);
    high_score_text.setFillColor(sf::Color::Yellow);

    high_score_text.setPosition(sf::Vector2f(window_.getSize().x-titleRect.width/half,
                                        high_score_text.getCharacterSize()/half));

    window_.draw(score_text);
    window_.draw(level_text);
    window_.draw(high_score_text);
}

void presentationLayerClass::displayGameObjects(const std::vector<std::shared_ptr<entityBaseClass>>& gameObjects, const int lives, const int score, const int highScore, std::tuple<const int, const int>levelInfo)
{
    window_.clear();
    displayLives(lives, score, highScore, levelInfo);
    for(const auto& object: gameObjects)
    {
        sf::Sprite gameobjectSprite = makeSprite(object);
        gameobjectSprite.setPosition(object->getPosition().getX_position(), object->getPosition().getY_position());
        window_.draw(gameobjectSprite);
    }

    window_.display();
    animateObjects(0.060f);
}

void  presentationLayerClass::animateObjects(float speed)
{
   for(auto& spriteTexture : spriteSheets)
   {
       if(spriteTexture.getObjectType()!=movingObjetsType::MUSHROOM)
       {
           auto time=speed;
           if(spriteTexture.getObjectType()==movingObjetsType::SCORPION)
            time/=4.0f;
           spriteTexture.update(time);
       }//if
   }//for
}

sf::Sprite presentationLayerClass::makeSprite(const shared_ptr<entityBaseClass>& object)
{
   auto MapTexture_iterator = gameTexture.find(object->getObjectType());
   sf::Sprite gameobjectsSprite; auto halfConstant = 2.0f;
   if(object->getObjectType() == movingObjetsType::BULLET || object->getObjectType() == movingObjetsType::PLAYER)
   {
       gameobjectsSprite.setOrigin((MapTexture_iterator->second).getSize().x/halfConstant, (MapTexture_iterator->second).getSize().y/halfConstant);
   } else
     {
        gameobjectsSprite = makeSpriteFromSpriteMarkerClass(object);
      }
   gameobjectsSprite.setTexture(MapTexture_iterator->second);
   return gameobjectsSprite;
}

sf::Sprite presentationLayerClass::makeSpriteFromSpriteMarkerClass(const shared_ptr<entityBaseClass>& object)
{
   auto entity_type = object->getObjectType(); //auto MapTexture_iterator = gameTexture.find(entity_type);
   sf::Sprite gameobjectsSprite; auto halfConstant = 2.0f;
   auto Vector_iterator = std::find_if(spriteSheets.begin(), spriteSheets.end(), [&, entity_type](const spriteMarkerClass& Sprite_Sheet){
                                       return (Sprite_Sheet.getObjectType() == entity_type); } );
   auto TextureRect = sf::IntRect();
    if(entity_type == movingObjetsType::CENTIPEDE){
          auto centipede_ = std::dynamic_pointer_cast<centipedeClass>(object);
          if(centipede_->getCentiBodyType() == CentiBodyType::BODY)
            ++Vector_iterator;
          TextureRect = Vector_iterator->getTextureRect(centipede_->getDirection());
          gameobjectsSprite.setRotation(centipede_->getAngulation());
      }
   else if(entity_type == movingObjetsType::MUSHROOM){
      if(object->isPoisoned())
        ++Vector_iterator;
      auto maxMushroomLIves = 4, mushColumn = maxMushroomLIves - object->getLives();
        TextureRect = Vector_iterator->getTextureRect(mushColumn);
      }else if(entity_type == movingObjetsType::SCORPION)
    {
        auto scorpion = std::dynamic_pointer_cast<entityMovementBaseClass>(object);
        TextureRect = Vector_iterator->getTextureRect(scorpion->getDirection());

    }/*else if(entity_type == movingObjetsType::FLEA)
    {

        auto flea = std::dynamic_pointer_cast<entityMovementBaseClass>(object);
        TextureRect = Vector_iterator->getTextureRect(flea->getDirection());
        //gameobjectsSprite.setOrigin(0,0);
        //gameobjectsSprite.scale(1,1);

    } */else {
           TextureRect = Vector_iterator->getTextureRect(objectsDirection::DOWN);
      }//if-elseif-elseif-else
      gameobjectsSprite.setTextureRect(TextureRect);
      gameobjectsSprite.setOrigin(std::abs(TextureRect.width/halfConstant),std::abs(TextureRect.height/halfConstant));
      return gameobjectsSprite;
}

void presentationLayerClass::ProccessEvents()
{
   sf::Event event;
   while(window_.pollEvent(event))
   {
       switch(event.type)
       {
       case sf::Event::Closed:
        window_.close();
        break;
       case sf::Event::KeyPressed:
        checkUpdatePressedKey(true, event.key.code);
        break;
       case sf::Event::KeyReleased:
        checkUpdatePressedKey(false, event.key.code);
        break;
       default:
        break;
       } //switch
   } //while
}

void presentationLayerClass::checkUpdatePressedKey(const bool ifKeyPressed, const sf::Keyboard::Key key)
{
   if(key == sf::Keyboard::Left) KeyboardInputKey_.isLeftButtonPressed=ifKeyPressed;
   if(key == sf::Keyboard::Right) KeyboardInputKey_.isRightButtonPressed=ifKeyPressed;
   if(key == sf::Keyboard::Up) KeyboardInputKey_.isUpButtonPressed=ifKeyPressed;
   if(key == sf::Keyboard::Down) KeyboardInputKey_.isDownButtonPressed=ifKeyPressed;
   if(key == sf::Keyboard::Space) KeyboardInputKey_.isSpaceButtonPressed=ifKeyPressed;
}

bool presentationLayerClass::ifWindowOpen() const
{
    return window_.isOpen();
}

bool presentationLayerClass::ifDownKeyPressed()
{
    return KeyboardInputKey_.isDownButtonPressed;
}

bool presentationLayerClass::ifUpKeyPressed()
{
    return KeyboardInputKey_.isUpButtonPressed;
}

bool presentationLayerClass::ifLeftKeyPressed()
{
    return KeyboardInputKey_.isLeftButtonPressed;
}

bool presentationLayerClass::ifRightKeyPressed()
{
    return KeyboardInputKey_.isRightButtonPressed;
}

bool presentationLayerClass::ifSpaceKeyPressed()
{
    return KeyboardInputKey_.isSpaceButtonPressed;
}

