#include "ScorpionClass.h"
#include <ctime>

struct ScorpionDimensions Scorpion::dimensions_;
Scorpion::Scorpion(const ScreenParameters& Screen_Parameters_)
: ScreenParameters_{Screen_Parameters_},
  isAlive_{true}
{
    srand(time(0));
    auto row = rand()%15 + 10;
    position_.setYposition(round(row*16.0f +24.0f));
    direction_ = static_cast<objectsDirection>(rand()%2 + 2);

    if(direction_ == objectsDirection::LEFT)
      position_.setXposition(ScreenParameters_.getwidth()-(dimensions_.width/2.0f + 1.0f));
    else position_.setXposition(dimensions_.width/2.0f + 1.0f);

}

void Scorpion::moveLeft()
{
    float maxWidth = ScreenParameters_.getwidth();
    auto newXPos = position_.getX_position()- dimensions_.speed;
    newXPos = (round(newXPos*10))/10;
    if(newXPos < maxWidth && newXPos > 0)
    {
        position_.setXposition(newXPos);
    }
    else
    {
        eliminated();
    } // if-else
}

void Scorpion::moveRight()
{
    float maxWidth = ScreenParameters_.getwidth();
    auto newXPos = position_.getX_position()+ dimensions_.speed;

    newXPos = (round(newXPos*10))/10;


    if(newXPos < maxWidth && newXPos > 0)
    {
        position_.setXposition(newXPos);
    }
    else
    {
        eliminated();
    } //if-else
}

void Scorpion::move()
{
    if(direction_ == objectsDirection::LEFT) moveLeft();
    else if(direction_ == objectsDirection::RIGHT) moveRight();
}

objectsDirection Scorpion::getDirection() const
{
    return direction_;
}

void Scorpion::setDirection(objectsDirection direction)
{
    direction_ = direction;
}

movingObjetsType Scorpion::getObjectType() const
{
    return movingObjetsType::SCORPION;
}

positionHandler Scorpion::getPosition() const
{
    return position_;
}

boundaryHandler Scorpion::getBoundary()
{
    return boundaryHandler{dimensions_.width,dimensions_.height,0.0, position_};
}

bool Scorpion::isAlive() const
{
    return isAlive_;
}

void Scorpion::eliminated()
{
    isAlive_ = false;
}

void Scorpion::reincarnate()
{
    isAlive_ = true;
}

int Scorpion::getLives()  const
{
    if(isAlive()) return 1;
    return 0;
}

bool Scorpion::isPoisoned() const
{
    return false;
}

void Scorpion::poison()
{
    return;
}

int Scorpion::getPoints() const
{
    auto hitPoints = 40;
    return hitPoints;
}


Scorpion::~Scorpion()
{
    //dtor
}
