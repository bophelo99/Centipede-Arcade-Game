#include "positionHandler.h"

positionHandler::positionHandler(float x, float y)
:xPosition{x},
 yPosition{y}
{
    //ctor
}

positionHandler positionHandler::operator -(const positionHandler& rhs)
{
   return positionHandler(xPosition-rhs.xPosition, yPosition-rhs.yPosition);
}

bool positionHandler::operator==(const positionHandler& rhs) const
{
   return (xPosition == rhs.xPosition && yPosition == rhs.yPosition);
}

float positionHandler::getX_position() const
{
   return xPosition;
}

float positionHandler::getY_position() const
{
    return yPosition;
}

 void positionHandler::setXposition(float XPosition)
 {
   xPosition = XPosition;
 }

 void positionHandler::setYposition(float YPosition)
 {
     yPosition = YPosition;
 }

 positionHandler::~positionHandler()
{
    //dtor
}
