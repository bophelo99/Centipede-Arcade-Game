#include "boundaryHandler.h"

boundaryHandler::boundaryHandler(float width, float height, float rotationAngle, positionHandler centreposition)
:height_{height},
 width_{width},
 rotationAngle_{rotationAngle},
 centreposition_{centreposition}
{
    //ctor
    computeBoundary();
}

boundaryHandler::~boundaryHandler()
{
    //dtor
}

positionHandler boundaryHandler::computeVertex(float radius, float angle)
{
  float xPos = radius*cos(angle+(rotationAngle_*PI/180.0f)) + centreposition_.getX_position();
  float yPos = centreposition_.getY_position() - radius*sin(angle+(rotationAngle_*PI/180.0f));
  return positionHandler{xPos,yPos};
}

tuple<float, float> boundaryHandler::getAngulation(float opp, float adj)
{
  auto angle = atan(opp/adj), radius = opp/sin(angle); return {angle, radius};
}

void boundaryHandler::sortPoint()
{
  auto Holdvertex = vertices; vertices.clear();
  auto Ymin_iterator = begin(Holdvertex), Ymax_iterator = begin(Holdvertex),
       Xmin_iterator = begin(Holdvertex), Xmax_iterator = begin(Holdvertex);
  for(auto Holdvertex_iterator = Holdvertex.begin()+1; Holdvertex_iterator!=end(Holdvertex); Holdvertex_iterator++ )
  {
      auto Xpos = Holdvertex_iterator->getX_position(), Ypos = Holdvertex_iterator->getY_position();
      if(Xpos>Xmax_iterator->getX_position())
      {
          Xmax_iterator = Holdvertex_iterator;
      } else if (Xpos<Xmin_iterator->getX_position())
        {
            Xmin_iterator = Holdvertex_iterator;
        }
      if(Ypos>Ymax_iterator->getY_position())
      {
         Ymax_iterator = Holdvertex_iterator;
      } else if(Ypos<Ymin_iterator->getY_position())
        {
            Ymin_iterator = Holdvertex_iterator;
        }
  }
  vertices.push_back(*Xmin_iterator); vertices.push_back(*Ymin_iterator); vertices.push_back(*Ymax_iterator); vertices.push_back(*Xmax_iterator);
}

void boundaryHandler::computeBoundary()
{
   auto [angle, radius] = getAngulation(width_/2.0f, height_/2.0f);
   angle+=PI/2.0f;
   auto vertex1 = computeVertex(radius, angle), vertex4 = computeVertex(radius, angle+PI);
   auto[angle1, radius1] = getAngulation(height_/2.0f,width_/2.0f);
   auto vertex2 = computeVertex(radius1, angle1), vertex3 = computeVertex(radius1, angle1+PI);
   if(rotationAngle_ == 0)
   {
     vector<positionHandler> holdVertices{vertex1, vertex2, vertex3, vertex4};
     vertices =  holdVertices;
   } else if(rotationAngle_ == -90 || rotationAngle_ == 270)
     {
        vector<positionHandler> holdVertices{vertex3, vertex1, vertex4, vertex2};
        vertices = holdVertices;
     } else if(rotationAngle_ == -180 || rotationAngle_ == 180)
       {
           vector<positionHandler> holdVertices{vertex4, vertex3, vertex2, vertex1};
           vertices = holdVertices;
       }  else if(rotationAngle_ == 90 || rotationAngle_ == -270)
          {
            vector<positionHandler> holdVertices{vertex2, vertex4, vertex1, vertex3};
              vertices = holdVertices;
          }else
           {
               vector<positionHandler> holdVertices{vertex1, vertex2, vertex3, vertex4};
               vertices = holdVertices;
               sortPoint();
           }
}

vector <positionHandler> boundaryHandler::getVertices() const
{
   return vertices;
}
