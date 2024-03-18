#ifndef SPLITAXIS_H
#define SPLITAXIS_H
#include "positionHandler.h"
#include "boundaryHandler.h"

#include <cmath>
#include <limits>
#include <algorithm>
#include <tuple>
#include <vector>

using std::numeric_limits;
using std::min;
using std::max;

/** \class SplitAxis
 *  \brief This is a class used to determine overlap between BoundaryBox objects.
 *         This class makes use of the Separating Axis Theorem algorithm that checks for
 *         overlap between convex polygons. The polygons implemented are Rectangle shapes
 *         which are created in the BoundaryBox class.
 *         The algorithm checks for overlap along all edges of the two BoundaryBox objects
 *         being checked. Projects the vertices of the BoundaryBox objects onto four axes.
 *         The axes are generated from the edges of the BoundaryBox objects, two from each one.
 *         The projections are then used to check for overlap.
 *         If a any of the axis detect no overlap, the algorithm returns false for no overlap.
 *         Otherwise, the other axis are checked for overlap. The Minimum Translation Vector
 *         (MTV) is also calculated in order to move BoundaryBox objects out of overlap.
 *  \author 1932442 Bophilo Ntsemi and 1839578 Masilo Sekhele
 *  \version 3.0
 */

class SplitAxis
{
    public:

        /** \fn bool checkOverlap(const boundaryHandler& rect_A, const boundaryHandler& rect_B);
         * \brief Takes in two boundaryHandler objects and checks whether they overlap.
         *  \param rect_A is of type boundaryHandler taken in by reference.
         *  \param rect_B is of type boundaryHandler taken in by reference.
         *  \return bool which is true if there's overlap and false otherwise.
         */
        bool checkOverlap(const boundaryHandler& rect_A, const boundaryHandler& rect_B);

         /** \fn positionHandler getDistance(positionHandler& centre1, positionHandler& centre2);
          * \brief Returns the minimum distances x and y to remove objects out of
         *          collision.
         * 	\param centre1 is of type positionHandler and is the centre of a boundaryHandler Shape.
         * 	\param centre_2 is of type positionHandler and is the centre of a boundaryHandler Shape.
         * 	\return positionHandler
         */
        positionHandler getDistance(positionHandler& centre1, positionHandler& centre2);

    protected:

    private:
        /** //private variables
        */
        vector<positionHandler> axes;
        vector<positionHandler> rectA_vertices;
        vector<positionHandler> rectB_vertices;
        float smallest_overlap = numeric_limits<float>::max();
        positionHandler min_translation_vector;

        //private memeber unctions
       /** \fn void generateAxes();
         * \brief Generates the normals perpendicular to the edges of a Rectangle.
         *        The normals are stored in a vector of type positionHandler.
		 *	      These normals are used as an axes for vector projection later on.
        */
        void generateAxes();

        /** \fn float dotProduct(const positionHandler& pointA, const positionHandler& pointB);
         * \brief Performs the dot product between two points.
         *  \param pointA is of type positionHandler.
         *  \param pointB is of type positionHandler.
         *  \return float which is the scalar result of the dot product.
         */
        float dotProduct(const positionHandler& pointA, const positionHandler& pointB);

        /** \fn positionHandler normalizeAxis(const positionHandler& axis);
        *  \brief Performs the normalization of an axis normal vector.
	    *	        The unit vector is what gets returned.
        *   \param axis is of type positionHandler.
        *   \return positionHandler which is the normalized axis vector (unit vector).
        */
        positionHandler normalizeAxis(const positionHandler& axis);

        /** \fn uple<float, float> projectVectorsOnAxis(const positionHandler& axis, vector<positionHandler>& vertices);
         * \brief Performs vector projection onto axes generated.
         *         The vertices of a Rectangle, boundary box, are projected onto an axis to
         *         determine where on the axis it is located. It returns the min and max
         *         projections of the Rectangle on the axis given.
         *  \param axis is of type positionHandler.
         *  \param vertices is a vector of type positionHandler.
         *  \return tuple<float,float> first float is the min projection of the Rectangle.
         *          Second float is the max projection of the Rectangle.
         */
        tuple<float, float> projectVectorsOnAxis(const positionHandler& axis, vector<positionHandler>& vertices);

        /** \fn bool checkProjectionOverlap();
         *  \brief Iterates through the axes generated and checks for overlap on each.
		 *	       Each BoundaryHandler's vertices are projected onto an axis by
         *         using projectVectorsOntoAxis.
         *         If overlap occurs on each axis then true is returned, otherwise false.
         *  \return bool
         */
        bool checkProjectionOverlap();

        /** \fn void clearAll();
         *  \brief Clears all the vectors used as private members.
        */
        void clearAll();
};

#endif // SPLITAXIS_H
