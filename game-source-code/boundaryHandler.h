
#ifndef BOUNDARYHANDLER_H
#define BOUNDARYHANDLER_H

#include  "POSITIONHANDLER.H"
#include <vector>
#include <tuple>
#include <cmath>

using std::tuple;
using std::vector;
using std::begin;
using std::end;
const auto PI = std::atan(1)*4;

/** \class boundaryHandler
 *  \brief This class constructs a rectangle shape with the given the width, height,
 *	       center and rotation angle if any. The construction requires the centre point
 *         of the rectangle shape to be given. The vertices of the boundaryHandler box are then
 *         calculated using the centre point and the rotation angle. These vertices are
 *         stored in a vector of type Position in the order upper left, upper right,
 *         bottom left, and bottom right.
 *  \author 1932442 Bophilo Ntsemi and 1839578 Masilo Sekhele
 *  \version 3.0
 */

class boundaryHandler
{
    public:

         /** \fn boundaryHandler(float width, float height, float rotationAngle, positionHandler centreposition);
         * \brief Parameterized Constructor. Creates a boundaryHandler Box object.
         * 	\param v is of type boundaryHandler and holds the centre position of the box.
         * 	\param width is of type float and holds the full width of the box.
         * 	\param height is of type float and holds the full height of the box.
         * 	\param rotationAngle is of type float and holds the rotated angle of the box, if any).
         */
        boundaryHandler(float width, float height, float rotationAngle, positionHandler centreposition);

         /** \fn vector <positionHandler> getVertices() const;
          * \brief A function that returns the vertices of the boundary box in
         *          a vector of type Position. The order of the vertices is upper left,
         *          upper right, bottom left, and bottom right.
         *  \return vector<positionHandler> containing the vertices of the boundary box.
         */
        vector <positionHandler> getVertices() const;

        /** \fn ~boundaryHandler();
         * \brief Default Destructor. Destroys a Boundary box.
         */
        ~boundaryHandler();

    protected:

    private:
        float height_, width_, rotationAngle_;
        /**
        */
        positionHandler centreposition_;
        vector<positionHandler> vertices;

        /** \fn positionHandler computeVertex(float radius, float angle);
         * \brief Calculates the vertex of the boundary box.
         *         Given a radius from the centre point and the angle relative to
         * 	       the centre point, a vertex can be calculated. These values are obtained by
         * 	       constructing the rectangle shape at a rotation of zero degrees.
         *  \param radius is a float and contains the radius (half diagonal length) from centre.
         *  \param angle is a float and contains the angle a vertex is from the centre's axis.
         *  \return positionHandler which is a vertex.
         */
         positionHandler computeVertex(float radius, float angle);

        /** \fn tuple<float, float> getAngulation(float opp, float adj);
         * \brief Takes in two sides of a right angled triangle and performs
         *         trig math to get a hypotenuse and angle between hypotenuse and adjacent.
         *  \param opp is a float and contains the length of the opposite side.
         *  \param adj is a float and contains the length of the adjacent side.
         *  \return tuple<float, float> containing the angle and the hypotenuse.
         */
         tuple<float, float> getAngulation(float opp, float adj);

        /** \fn  void computeBoundary();
         * \brief Builds a positionHandler box around a centre point with the parameters
         *         taken in by the constructor. Creates vertices using the computeVertex
		 *	       function. The created vertices are then saved into the private member
		 *	       vector vertices_ in the order specified. Gets called in the constructor to
		 *	       immediately create the positionHandler box once all the parameters needed are saved.
         */
         void computeBoundary();

         /** \fn void sortPoint();
          * \brief Iterates through the vertices of a rotated positionHandler box.
         *          The order of the vertices being saved is necessary for other
         *          classes that require it. This function pushes the generated vertices
         *          into a vector in the vertex order: Upper Left, Upper Right, Bottom Left
         *          and Bottom Right.
         */
         void sortPoint();
};

#endif // BOUNDARYHANDLER_H
