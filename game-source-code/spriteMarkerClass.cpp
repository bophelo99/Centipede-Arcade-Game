#include "spriteMarkerClass.h"
#include <cmath>
///
spriteMarkerClass::spriteMarkerClass(movingObjetsType objectType, objectsDirection direction, sf::Texture* ObjectTexture, unsigned int rows, const float time, sf::Vector2u image)
:objectType_{objectType},
 direction_{direction},
 time_{time},
 Tot_time_{0},
 rows_{rows},
 image_{image},
 PresentImage{0,rows}
{
     TexturRectAxis.height = ObjectTexture->getSize().y/static_cast<float>(image.y);
     TexturRectAxis.width = ObjectTexture->getSize().x/static_cast<float>(image.x);
}

movingObjetsType spriteMarkerClass::getObjectType() const
{
  return objectType_;
}

sf::IntRect spriteMarkerClass::getTextureRect(int column)
{
  PresentImage.x=column; createTextureRect(direction_);
  return TexturRectAxis;
}

sf::IntRect spriteMarkerClass::getTextureRect(objectsDirection Direction)
{
     createTextureRect(Direction);
     return TexturRectAxis;
}

void spriteMarkerClass::createTextureRect(objectsDirection direction)
{
  TexturRectAxis.top = PresentImage.y*TexturRectAxis.height; auto width = std::abs(TexturRectAxis.width);
  TexturRectAxis.left = std::abs(TexturRectAxis.width);
  if(direction==direction_ || direction==objectsDirection::DOWN || direction == objectsDirection::UP)
  {
      TexturRectAxis.left = PresentImage.x*width;
      TexturRectAxis.width = width;
  }else
     {
         TexturRectAxis.left = (PresentImage.x+1)*width;
         TexturRectAxis.width = -width;
     }  //if //else
}

void spriteMarkerClass::update(float Dtime)
{
   Tot_time_ +=Dtime;
   if(Tot_time_>=time_)
   {
       Tot_time_-=time_;
       ++PresentImage.x;
       if(PresentImage.x>=image_.x)
        PresentImage.x=0;
   }//if
}

spriteMarkerClass::~spriteMarkerClass()
{
 //dtor
}
