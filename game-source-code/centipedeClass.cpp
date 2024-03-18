#include "centipedeClass.h"
#include <cmath>
using std::round;
struct CentipedeDimension centipedeClass::centi_dimension;
centipedeClass::centipedeClass(const ScreenParameters& ScreenParameters_, CentiBodyType BodyType_, positionHandler position, objectsDirection direction)
:Screen_Parameters_{ScreenParameters_},
  position_{position},
  Centi_BodyType_{BodyType_},
  present_direction{direction}
{
    //ctor
    past_direction = objectsDirection::DOWN;
    ifBottom=false;
    CountDown=0;
    ifPoisonedChange = false;

}

centipedeClass::~centipedeClass()
{
    //dtor
}

movingObjetsType centipedeClass::getObjectType() const
{
   return movingObjetsType::CENTIPEDE;
}

positionHandler centipedeClass::getPosition() const
{
   return position_;
}

objectsDirection centipedeClass::getPastDirection() const
{
   return past_direction;
}

boundaryHandler centipedeClass::getBoundary()
{
   return boundaryHandler{centi_dimension.width, centi_dimension.height, 0.0, position_};
}

objectsDirection centipedeClass::getDirection() const
{
    return present_direction;
}

CentiBodyType centipedeClass::getCentiBodyType() const
{
    return Centi_BodyType_;
}

void centipedeClass::switchDirection()
{
    if(past_direction==objectsDirection::DOWN)
    {
        setDirection(objectsDirection::DOWN);
    }
    else if(past_direction==objectsDirection::UP)
    {
        setDirection(objectsDirection::UP);
    } //if - else if
}

void centipedeClass::setCentiBodyType(CentiBodyType BodyType)
{
    if(BodyType == CentiBodyType::HEAD) remove_if_HeadCollisions();
    Centi_BodyType_ = BodyType;
}

float centipedeClass::getAngulation() const
{
   return angulation;
}

void centipedeClass::remove_if_HeadCollisions()
{
    HeadCollisions.clear();
    IfPoisonedHeadCollisions.clear();
}

void centipedeClass::store_collision(positionHandler position, bool headPosionedCollision)
{
   if(Centi_BodyType_== CentiBodyType::HEAD){
       remove_if_HeadCollisions(); return;
   }
   auto totalCollisions = count(HeadCollisions.begin(),HeadCollisions.end(), position);
   if(totalCollisions == 0)
   {
        IfPoisonedHeadCollisions.push_back(headPosionedCollision);
     HeadCollisions.push_back(position);
   }
}

void centipedeClass::move()
{
    if(EntryMovement()) return;
    if(ifPoisonedMovement){
        ifPoisoned = false;
    }
    if(!ifPoisoned){
        if(Centi_BodyType_==CentiBodyType::BODY)
            if_HeadCollisions();
        switch(present_direction)
        {
          case objectsDirection::DOWN:
                 //angulation=0.0f;
                 moveDown();
                 break;
          case objectsDirection::LEFT:
                 angulation=0.0f;
                 moveLeft();
                 break;
          case objectsDirection::RIGHT:
                 angulation=0.0f;
                 moveRight();
                 break;
          case objectsDirection::UP:
                 moveUp();
                 break;
           default:
                 break;
        }
    } else
    {
       if_PoisonedMovement();
    }
}

bool centipedeClass::EntryMovement()
{
    auto halfScreenWidth = Screen_Parameters_.getwidth()/2.0f;
   if(position_.getY_position() < 0 && present_direction == objectsDirection::LEFT)
    {
        if(position_.getX_position()<halfScreenWidth)
   {
       moveDown(); moveDown(); return true;
   }
    }
   else if(position_.getY_position() < 0 && present_direction == objectsDirection::RIGHT)
   {
       if(position_.getX_position()>halfScreenWidth)
   {
       moveDown(); moveDown(); return true;
   }
   }
   return false;
}

void centipedeClass::moveRight()
{
    float HorizontalLimitPosition = Screen_Parameters_.getwidth()-(centi_dimension.width/2.0f);
    auto newX_position = position_.getX_position()+centi_dimension.speed;
    if(ifBottom && isPoisoned())
    {
      newX_position = position_.getX_position()+(centi_dimension.width+1);
    } newX_position = (round(newX_position*10))/10;
    if(newX_position<HorizontalLimitPosition)
    {
        position_.setXposition(newX_position);


    } else
    {
        if(past_direction==objectsDirection::UP)
        {
            setDirection(objectsDirection::UP); moveUp();
        } else if(past_direction==objectsDirection::DOWN)
        {
            setDirection(objectsDirection::DOWN); moveDown();
        }
    }
}

void centipedeClass::moveLeft()
{
   float HorizontalLimitPosition = Screen_Parameters_.getwidth()-(centi_dimension.width/2.0f);
    auto newX_position = position_.getX_position()-centi_dimension.speed;
    if(ifBottom && isPoisoned())
    {
      newX_position = position_.getX_position()-(centi_dimension.width+1);
    } newX_position = (round(newX_position*10))/10;
    if(newX_position<HorizontalLimitPosition && newX_position>(centi_dimension.width/2.0f))
    {
        position_.setXposition(newX_position);
    } else
    {
        if(past_direction==objectsDirection::UP)
        {
            setDirection(objectsDirection::UP); moveUp();
        } else if(past_direction==objectsDirection::DOWN)
        {
            setDirection(objectsDirection::DOWN); moveDown();
        }
    }
}

void centipedeClass::moveUp()
{
   float verticalLimitPosition = Screen_Parameters_.getheight()-(Screen_Parameters_.getheight()*0.2);
   auto newY_position = position_.getY_position()-centi_dimension.DownSlideSpeed;
   if(newY_position>verticalLimitPosition)
   {
      position_.setYposition(newY_position);
      if(past_direction==objectsDirection::LEFT){

          setDirection(objectsDirection::RIGHT);
          moveRight();
          angulation = 45.0f;
          past_direction = objectsDirection::UP;
       }  else{
          setDirection(objectsDirection::LEFT);
          moveLeft();
          angulation = -45.0f;
          past_direction = objectsDirection::UP;
       }
   } else
   {
       moveDown();
   }
}

void centipedeClass::moveDown()
{
   float verticalLimitPosition = Screen_Parameters_.getheight()-(centi_dimension.height/2.0f);
   auto newY_position = centi_dimension.DownSlideSpeed+position_.getY_position();
   if(newY_position<=verticalLimitPosition)
   {
       position_.setYposition(newY_position);
       if(past_direction==objectsDirection::LEFT)
        {
          setDirection(objectsDirection::RIGHT);
          moveRight();
          angulation = 45.0f;
          past_direction = objectsDirection::DOWN;
       }
        else{
          setDirection(objectsDirection::LEFT);
          moveLeft();
          angulation = -45.0f;
          past_direction = objectsDirection::DOWN;

       }
   } else
   {
      ifBottom=true;
      moveUp();
     ifBottom=false;
     ifPoisonedMovement = true;
   }
}

void centipedeClass::if_HeadCollisions()
{
    if(HeadCollisions.empty()) return;

      auto Position = HeadCollisions.begin();
      auto PoisonedPosition = IfPoisonedHeadCollisions.begin();
      if(position_ == *Position)
      {
          if(*PoisonedPosition) poison();
          else switchDirection();
          HeadCollisions.erase(Position);
          IfPoisonedHeadCollisions.erase(PoisonedPosition);
      }

   return;
}

void centipedeClass::if_PoisonedMovement()
{
   auto speedFactor =static_cast<int>(round(centi_dimension.width/centi_dimension.speed));
   ifPoisonedMovement = false;
   if(CountDown == 0)
   {
       setDirection(objectsDirection::DOWN);
       moveDown();
       ifPoisonedChange = !ifPoisonedChange;
   } else
   {
       if(ifPoisonedChange)
       {
          setDirection(objectsDirection::LEFT);
          moveLeft();
       }
        if(!ifPoisonedChange)
       {
          setDirection(objectsDirection::RIGHT);
          moveRight();
       }
   }
   CountDown = ((++CountDown)%(speedFactor));
}

void centipedeClass::setDirection(objectsDirection direction)
{
     past_direction = present_direction;
     present_direction=direction;
}

void centipedeClass::eliminated()
{
   ifAlive = false;
}

void centipedeClass::poison()
{
 ifPoisoned=true;
}

void centipedeClass::reincarnate()
{
  return;
}

bool centipedeClass::isAlive() const
{
 return ifAlive;
}

bool centipedeClass::isPoisoned() const
{
   return ifPoisoned;
}

int centipedeClass::getLives() const
{
  if(isAlive()) return 1;
  return 0;
}

int centipedeClass::getPoints() const
{
    auto score = 100;
   return score;
}
