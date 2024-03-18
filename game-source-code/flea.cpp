#include "flea.h"
#include <ctime>
#include <cmath>
using std::round;

struct fleaDimensions flea::dimensions_;
positionHandler screenCoordinate(positionHandler position);
positionHandler LinkingCoordinates(positionHandler position);

flea::flea(const ScreenParameters& Screen_Parameters_)
:ScreenParameters_{Screen_Parameters_},
 poisoned{false},
 isAlive_{true},
 numberOfLives{2}
{
    srand(time(0));
    direction_ = objectsDirection::DOWN;

    auto Cellsize = 16;
    auto maxRow = static_cast<int>(floor(ScreenParameters_.getwidth()/Cellsize));
    auto InitalXPos =rand()%maxRow, InitialYPos = 0;
    auto position = LinkingCoordinates(positionHandler(InitalXPos,InitialYPos));
    position = screenCoordinate(position);
    position_= LinkingCoordinates(position);

}

positionHandler screenCoordinate(positionHandler position)
{
    if (position.getX_position()>= 624.0) position.setYposition(0.0);
    auto x = round((position.getX_position()-8.0)/16.0);
    auto y = round((position.getY_position()-24.0)/16.0);
    return positionHandler(x,y);
}

positionHandler LinkingCoordinates(positionHandler position)
{
  auto x=round(position.getX_position()*16+8.0),  y=round(position.getY_position()*16+24.0);
  return positionHandler(x,y);
}


movingObjetsType flea::getObjectType() const
{
  return movingObjetsType::FLEA;
}

positionHandler flea::getPosition() const
{
   return position_;
}

boundaryHandler flea::getBoundary()
{
  return boundaryHandler{dimensions_.width, dimensions_.height, 0.0f, position_};
}

objectsDirection flea::getDirection() const
{
   return direction_;
}

void flea::moveDown()
{
   float verticalLimitPosition = ScreenParameters_.getheight()-(dimensions_.height/2.0f);
   auto newY_position = dimensions_.speed + position_.getY_position();
   if(newY_position<verticalLimitPosition)
   {
       position_.setYposition(newY_position);
   }
   else
   {
       eliminated();
   }
}

void flea::move()
{
   if(direction_ == objectsDirection::DOWN) moveDown();
}

void flea::setDirection(objectsDirection direction)
{
  direction_ = objectsDirection::DOWN;
}

void flea::eliminated()
{
  looseLive();
  if(numberOfLives<=0){

    isAlive_ = false;
    }
}

void flea::poison()
{
  return;
}

void flea::reincarnate()
{
   return;
}

bool flea::isAlive() const
{
 return isAlive_;
}

bool flea::isPoisoned() const
{
  return false;
}

int flea::getLives() const
{
   return numberOfLives;
}

int flea::getPoints() const
{
  auto hitPoints = 200;
    return hitPoints;
}

void flea::looseLive()
{
   numberOfLives--;
}

 flea::~flea()
 {
   // dtor
 }
