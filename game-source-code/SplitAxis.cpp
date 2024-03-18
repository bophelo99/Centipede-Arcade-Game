#include "SplitAxis.h"

bool SplitAxis::checkOverlap(const boundaryHandler& rect_A, const boundaryHandler& rect_B)
{
    if(!axes.empty()) clearAll();
    rectA_vertices = rect_A.getVertices();
    rectB_vertices = rect_B.getVertices();
    generateAxes();
    return checkProjectionOverlap();
}

positionHandler SplitAxis::getDistance(positionHandler& centre1, positionHandler& centre2)
{
   positionHandler B_to_A = centre2-centre1;
   if(dotProduct(min_translation_vector, B_to_A)>=0)
   {
       min_translation_vector=positionHandler{0.0} - min_translation_vector;
   } // if
   return(positionHandler(min_translation_vector.getX_position()*smallest_overlap, min_translation_vector.getY_position()*smallest_overlap));
}

void SplitAxis::generateAxes()
{
    //rectA
    //UpperRIght-UpperLeft
   auto axis_ = rectA_vertices.at(1) - rectA_vertices.at(0);
   axes.push_back(normalizeAxis(axis_));
   //upperight-bottomright
   axis_ = rectA_vertices.at(1)-rectA_vertices.at(3);
   axes.push_back(normalizeAxis(axis_));
   //rectB
   //upperleft-bottomleft
   axis_ = rectA_vertices.at(0)-rectA_vertices.at(2);
   axes.push_back(normalizeAxis(axis_));
   //upperleft-bottomright
   axis_ = rectA_vertices.at(0)-rectA_vertices.at(1);
   axes.push_back(normalizeAxis(axis_));
}

float SplitAxis::dotProduct(const positionHandler& pointA, const positionHandler& pointB)
{
   float dot_prod = (pointA.getX_position()* pointB.getX_position()) + (pointA.getY_position()*pointB.getY_position());
   return dot_prod;
}

positionHandler SplitAxis::normalizeAxis(const positionHandler& axis)
{
   float axis_X = axis.getX_position(), axis_Y = axis.getY_position();
   float axis_magnitude = std::sqrt((std::pow(axis_X,2))+(std::pow(axis_Y,2)));
   return (positionHandler{axis_X/axis_magnitude, axis_Y/axis_magnitude});
}

tuple<float, float> SplitAxis::projectVectorsOnAxis(const positionHandler& axis, vector<positionHandler>& vertices)
{
   vector<positionHandler> projected_vertices(4);
   auto iter_projected_vertex = begin(projected_vertices);
  float axis_X = axis.getX_position(), axis_Y = axis.getY_position();
  float axis_magnitudeSquare = (std::pow(axis_X,2))+(std::pow(axis_Y,2));
  for(const auto& vertex: vertices)
  {
      float product = dotProduct(vertex, axis)/ axis_magnitudeSquare;
      iter_projected_vertex->setXposition(product*axis.getX_position());
      iter_projected_vertex->setYposition(product*axis.getY_position());
      ++iter_projected_vertex;
  } //for
    float minimumProjection = dotProduct(axis, projected_vertices.at(0));
    float maximumProjection = minimumProjection;

    //perform dot product between vwrtices and axis
    for(auto index=1u; index != projected_vertices.size(); index++){
        float projection = dotProduct(axis, projected_vertices.at(index));

        if (projection < minimumProjection) minimumProjection = projection;
        else if (projection > maximumProjection) maximumProjection = projection;
    } // for
    return {minimumProjection, maximumProjection};
}

bool SplitAxis::checkProjectionOverlap()
{
   for(const auto& axis: axes)
   {
       //project rectA
       auto[minPojectionA, maxProjectionA] = projectVectorsOnAxis(axis, rectA_vertices);
       //project rectB
       auto[minPojectionB, maxProjectionB] = projectVectorsOnAxis(axis, rectB_vertices);

       bool overlapOccured = (minPojectionB<=maxProjectionA && maxProjectionB>=minPojectionA);
       if(overlapOccured==false) return false;
       else {
            float overlap = std::max(0.0f, std::min(maxProjectionA, maxProjectionB));
            overlap-=std::max(minPojectionA, minPojectionB);
            if(overlap<smallest_overlap)
            {
                min_translation_vector = axis;
                smallest_overlap = overlap;
            }//if
       } //if // else
   } // for
   return true;
}

void SplitAxis::clearAll()
{
    axes.clear();
    rectA_vertices.clear();
    rectB_vertices.clear();
    smallest_overlap = numeric_limits<float>::max();
    min_translation_vector = positionHandler(0.0f, 0.0f);
}
