#include "PlayerClass.h"

PlayerClass::PlayerClass(const ScreenParameters& Screen_Parameters)
:score{0}, numberOFLives_{3}, ScreenParameters_{Screen_Parameters}, direction_{objectsDirection::NONE}
{
    //ctor
    position.setXposition(ScreenParameters_.getwidth()/2);
    position.setYposition(ScreenParameters_.getheight() - dimension.height*0.5);
}

movingObjetsType PlayerClass::getObjectType() const
{
 return movingObjetsType::PLAYER;
}

positionHandler PlayerClass::getPosition() const
{
  return position;
}

boundaryHandler PlayerClass::getBoundary()
{
  return boundaryHandler{dimension.width, dimension.height, 0.0, position};
}

objectsDirection PlayerClass::getDirection() const
{
  return direction_;
}

void PlayerClass::move()
{
   float currentYposition = 0, currentXposition = 0;
   float maxHeight = ScreenParameters_.getheight(), minHeight = maxHeight - maxHeight*0.2, maxWidth = ScreenParameters_.getwidth();
    switch(direction_)
    {
        case objectsDirection::DOWN:
          currentYposition = position.getY_position()+dimension.speed;
          if(currentYposition<=(maxHeight-8.0f)){ position.setYposition(currentYposition); }
          break;
        case objectsDirection::UP:
          currentYposition = position.getY_position()-dimension.speed;
          if(currentYposition>=minHeight) {position.setYposition(currentYposition);}
          break;
        case objectsDirection::LEFT:
          currentXposition = position.getX_position()-dimension.speed;
          if(currentXposition>=8.0f) {position.setXposition(currentXposition);}
          break;
        case objectsDirection::RIGHT:
          currentXposition = position.getX_position()+dimension.speed;
          if(currentXposition <= (maxWidth-8.0f)) {position.setXposition(currentXposition);}
          break;
        default:
            break;
    }
}

void PlayerClass::setDirection(objectsDirection direction)
{
  direction_ = direction;
}

void PlayerClass::eliminated()
{
   ifgotHit=true;
   numberOFLives_--;
}

void PlayerClass::poison()

{

}

void PlayerClass::reincarnate()
{
  if(isAlive())
  {
      position.setXposition(ScreenParameters_.getwidth()/2);
      position.setYposition(ScreenParameters_.getheight()-dimension.height*0.5);
      ifgotHit=false;
      weapon_.reset();
  }
}

bool PlayerClass::isAlive() const
{
   if(numberOFLives_>0) {return true;}
   return false;
}

bool PlayerClass::isPoisoned() const
{
  return false;
}

int PlayerClass::getLives() const
{
   return numberOFLives_;
}

int PlayerClass::getPoints() const
{
  return 0;
}

int PlayerClass::scoredetails() const
{
    return score;
}


 std::vector<std::shared_ptr<PlayerBullet>> PlayerClass::shoot_bullet()
 {
      auto Xposition = position.getX_position()-dimension.speed, Yposition = position.getY_position()-dimension.height;
      return weapon_.fire(ScreenParameters_, positionHandler{Xposition, Yposition});
 }

void PlayerClass::addscores(int scoreupdate)
{
    score +=scoreupdate;
}

void PlayerClass::upgradeGunShot()
{
    weapon_.upgradeWeapon();
}

bool PlayerClass::ifGotHit()
{
    return ifgotHit;
}

PlayerClass::~PlayerClass()
{
    //dtor
}
