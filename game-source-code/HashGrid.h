#ifndef HASHGRID_H
#define HASHGRID_H
#include "ScreenParameters.h"
#include "entityBaseClass.h"
#include "positionHandler.h"
/**
*/
#include <algorithm>
#include <memory>
#include <vector>
#include <map>
/**
*/
using std::unique_copy;
using std::sort;
using std::find;
using std::begin;
using std::end;
using std::vector;
using std::shared_ptr;
using std::map;
using std::pair;
using entityBaseClass_ptr = std::shared_ptr<entityBaseClass>;


/** \class HashGrid
 *  \brief This class will be used by collision detection to query for objects
 *         around the object of interest. The screen is divided up into cells. A map will be
 *         populated with the cell's id as a key and the value will be a stl vector container
 *         that has shared_ptr(s) to game objects in each cell. Shared pointers to other
 *	       objects will be returned for cells where an object exists.
 *  \author 1932442 Bophilo Ntsemi and 1839578 Masilo Sekhele
 *  \version 3.0
 */
class HashGrid
{
    public:
        /** \fn HashGrid(const ScreenParameters Screen_Parameters_);
         * \brief Parameterized constructor. Creates a HashGrid object.
         *  \param grid is of type Grid and has the screen's width and height
         */
        HashGrid(const ScreenParameters Screen_Parameters_);

        /** \fn ~HashGrid();
         * \brief Default Destructor. Destroys a SpatialHash object.
         */
         ~HashGrid();

        /** \fn void constructSpatialGrid(vector<entityBaseClass_ptr>& gameobjects);
         * \brief Saves the cell locations of an object into a map which will be
         * 	       used to query the objects near it.
         * 	\param game_objects is vector of entityBaseClass and contains the game objects created in the game.
         * 	       S\return void
         */
        void constructSpatialGrid(vector<entityBaseClass_ptr>& gameobjects);

        /** \fn std::vector<entityBaseClass_ptr> DetectNearObjects(entityBaseClass_ptr objects);
         * \brief Queries the map for the cells the object is located in and
         * 	       returns a vector of shared pointers to all the objects in the cells
         * 	       where the object of interest is located.
         * 	\param object is a shared pointer of type IEntity.
         * 	\return vector<shared_ptr<entityBaseClass>>
         */
        std::vector<entityBaseClass_ptr> DetectNearObjects(entityBaseClass_ptr objects);

       /** \fn void remove();
         * \brief Clears the vectors in the gameObjects.
         * \return void
         */
        void remove();


    protected:

    private:
        unsigned int cellSize;
        ScreenParameters ScreenParameters_;
        /**
        */
        std::map<unsigned int, std::vector<entityBaseClass_ptr>> gameObjects;

        /** \fn void ConstructMap();
         * \brief Builds the map gameObjects.
         *         The keys are integers corresponding to cell ids and
		 *	       values are empty vectors in the beginning.
         * 	\return void
         */
        void ConstructMap();

        /** \fn vector<positionHandler> getObjectPositions(entityBaseClass_ptr& object);
         * \brief Retrieves the screen positions where the object's centre and
         * 	       boundary box vertices are located.
         * 	\param object a shared pointer of type entityBaseClass taken by reference.
         * 	\return vector<positionHandler>
         */
        vector<positionHandler> getObjectPositions(entityBaseClass_ptr& object);

        /** \fn vector<unsigned int> makeMapKeys(std::vector<positionHandler>& positions);
         * \brief Maps positions to a cell based on the grid's width, height, and
         * 	       the chosen cell size.
         * 	\param positions is a vector of type positionHandler.
         * 	\return vector<unsigned int>
         */
        vector<unsigned int> makeMapKeys(std::vector<positionHandler>& positions);

        /** \fn void storePosition(entityBaseClass_ptr object);
         * \brief Saves a shared pointer to the object at the cells where the
         *	       object is located into the map gameObjects;
         *	\param object is a shared_ptr to entityBaseClass and is pointing to a game object.
         * 	\return void
         */
        void storePosition(entityBaseClass_ptr object);

        /** \fn unsigned int makeMapKey(const positionHandler& position)
         * \brief Maps a position to a cell based on the grid's width, height and
         * 	       the chosen cell size.
         * 	\param position is of type positionHandler taken by reference.
         * 	\return unsigned int
         */
        unsigned int makeMapKey(const positionHandler& position);
};
#endif // HASHGRID_H
