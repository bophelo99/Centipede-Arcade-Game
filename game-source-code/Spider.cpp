#include "Spider.h"
#include <ctime>
#include <cmath>

struct SpiderDimensions Spider::dimensions_;

Spider::Spider(const ScreenParameters& Screen_Parameters_)
:ScreenParameters_{Screen_Parameters_},
 isAlive_{true},
 turningPointAvailable_{false}
{
   srand(time(0));
   movementDirection_ = objectsDirection::DOWN;
    major_direction_ = static_cast<objectsDirection>(rand()%2+2); //left or right
    if(major_direction_ == objectsDirection::LEFT)
    {
        position_.setXposition(ScreenParameters_.getwidth()-(dimensions_.width/2.0f + 1.0f));
        position_.setYposition(ScreenParameters_.getheight()- ScreenParameters_.getheight()*0.2f);

    }else{
        position_.setXposition(dimensions_.width/2.0f + 1.0f);
        position_.setYposition(ScreenParameters_.getheight()- ScreenParameters_.getheight()*0.2f);
    }//if //else
}

void Spider::moveUp()
{

    float maxWidth  = ScreenParameters_.getwidth();
    float minHeight = ScreenParameters_.getheight()- ScreenParameters_.getheight()*0.25;
    auto newXpos = 0.f;
    auto newYpos = 0.f;
    if(!turningPointAvailable_)CalculateSlope();

    if(major_direction_ == objectsDirection::LEFT)newXpos = position_.getX_position()-dimensions_.speed;
    else newXpos = position_.getX_position()+dimensions_.speed;

    newYpos = position_.getY_position()- std::abs(slope_*dimensions_.speed);
    if(newXpos < 0 || newXpos > maxWidth){
        isAlive_ = false;
        return;
    }
    if(newYpos >= turningPoint_.getY_position() && newYpos >= minHeight)
    {
        position_.setXposition(newXpos);
        position_.setYposition(newYpos);
    }
    else
    {
        turningPointAvailable_ = false;
        movementDirection_ = objectsDirection::DOWN;
        moveDown();
    } // if-else
}

void Spider::moveDown()
{
    float maxWidth  = ScreenParameters_.getwidth();
    float maxHeight = ScreenParameters_.getheight()- dimensions_.height/2.0f;
    auto newXpos = 0.f;
    auto newYpos = 0.f;
    if(!turningPointAvailable_)CalculateSlope();

    if(major_direction_ ==objectsDirection::LEFT)newXpos = position_.getX_position()-dimensions_.speed;
    else newXpos = position_.getX_position()+dimensions_.speed;
     newYpos = position_.getY_position()+ std::abs(slope_*dimensions_.speed);
    if(newXpos < 0 || newXpos > maxWidth){
        isAlive_ = false;
        return;
    }
    if(newYpos <= turningPoint_.getY_position() && newYpos <= maxHeight){
        position_.setXposition(newXpos);
        position_.setYposition(newYpos);
    }
    else
    {
        turningPointAvailable_ = false;
        movementDirection_ = objectsDirection::UP;
        moveUp();
    }
}

void Spider::CalculateSlope()
{
    float minHeight = ScreenParameters_.getheight()- ScreenParameters_.getheight()*0.25;
    float maxHeight = ScreenParameters_.getheight()- dimensions_.height/2.0f;

    auto xpos = 0.0f;
    auto ypos = 0.0f;
    auto multFactor = 4;

     if(major_direction_ == objectsDirection::LEFT)
     xpos = rand()%static_cast<int>(multFactor*dimensions_.width) + multFactor*dimensions_.width + position_.getX_position();
     else  xpos = position_.getX_position() - rand()%static_cast<int>(multFactor*dimensions_.width) + multFactor*dimensions_.width;

      if(movementDirection_ == objectsDirection::DOWN)
    {
        auto y_difference = 0.5f*(maxHeight - position_.getX_position());
        ypos = rand()%static_cast<int>(y_difference) + position_.getY_position() + y_difference;

        turningPoint_.setXposition(xpos);
        turningPoint_.setYposition(ypos);

        slope_ = std::abs(position_.getY_position() - ypos)/std::abs(position_.getX_position() - xpos);
        turningPointAvailable_ = true;
    }
  else
    {
        auto y_difference = 0.5f*(position_.getY_position()-minHeight);
        ypos =  position_.getY_position() - rand()%static_cast<int>(y_difference);

        turningPoint_.setXposition(xpos);
        turningPoint_.setYposition(ypos);

        slope_= std::abs(position_.getY_position() - ypos)/std::abs(position_.getX_position() - xpos);
        turningPointAvailable_ = true;
    }

}

movingObjetsType Spider::getObjectType() const
{
    return movingObjetsType::SPIDER;
}

positionHandler Spider::getPosition() const
{
      return position_;
}

boundaryHandler Spider::getBoundary()
{
   return boundaryHandler{dimensions_.width, dimensions_.height, 0.0f, position_};
}

objectsDirection Spider::getDirection() const
{
  return major_direction_;
}

void Spider::move()
{
     switch(movementDirection_)
    {
        case objectsDirection::UP:
            moveUp();
            break;
        case objectsDirection::DOWN:
            moveDown();
            break;
        default:
            break;
    }//switch
}

void Spider::setDirection(objectsDirection direction)
{
    major_direction_ = direction;
}

void Spider::eliminated()
{
   isAlive_ = false;
}

void Spider::poison()
{
   return;
}

void Spider::reincarnate()
{
    return;
}

bool Spider::isAlive() const
{
    return isAlive_;
}

bool Spider::isPoisoned() const
{
    return false;
}

int Spider::getLives() const
{

    if(isAlive()) return 1;
    return 0;
}

int Spider::getPoints() const
{
     auto hitPoints = 200;
    return hitPoints;
}

Spider::~Spider()
{
   // dtor
}
