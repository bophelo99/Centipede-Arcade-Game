#include "ScreenParameters.h"

ScreenParameters::ScreenParameters(unsigned int width, unsigned int height )
:width_{width},
 height_{height}
{

}

unsigned int ScreenParameters::getheight() const
{
   return height_;
}

unsigned int ScreenParameters::getwidth() const
{
   return width_;
}

ScreenParameters::~ScreenParameters()
{
    //dtor
}
