#include "mushroomsClass.h"

struct MushroomDimensions mushroomsClass::dimensions_;

mushroomsClass::mushroomsClass(positionHandler position)
:position_{position},
 poisoned{false},
 Alive{true},
 numberOfLives{4}
{
    //ctor
}

mushroomsClass::~mushroomsClass()
{
    //dtor
}

positionHandler mushroomsClass::getPosition() const
{
   return position_;
}

movingObjetsType mushroomsClass::getObjectType() const
{
   return movingObjetsType::MUSHROOM;
}

boundaryHandler mushroomsClass::getBoundary()
{
   return boundaryHandler{dimensions_.width, dimensions_.height, 0.0,position_};
}

bool mushroomsClass::isAlive() const
{
  if(numberOfLives<=0)
  { return false;
  }  else return true;
}
bool mushroomsClass::isPoisoned() const
{
  return poisoned;
}

void mushroomsClass::eliminated()
{
  looseLive();
  if(numberOfLives<=0){
    Alive = false;
  }
}

void mushroomsClass::reincarnate()
{
  if(!isAlive()) return;
    numberOfLives = 4;
   poisoned = false;
}

void mushroomsClass::poison()
{
   poisoned = true;
}

int mushroomsClass::getLives() const
{
   return numberOfLives;
}

int mushroomsClass::getPoints() const
{
    if(isPoisoned()){
        return 2;
    }
     return 1;
}

void mushroomsClass::looseLive()
{
   numberOfLives--;
}
