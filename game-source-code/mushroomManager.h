#ifndef MUSHROOMMANAGER_H
#define MUSHROOMMANAGER_H
/**
*/
#include "mushroomsClass.h"
#include "ScreenParameters.h"
/**
*/
#include <memory>
#include <vector>
#include <map>
#include <cmath>
/**
*/
using std::map;
using std::pair;
using std::vector;
using std::shared_ptr;
using std::make_shared;

/** \class mushroomManager
 *  \brief Creates all the Mushroom objects of the game. The game grid is divided
 *  into cells of size 16x16 pixels. Each cell is paired with a bool indicating whether
 *  the cell is occupied or not. Mushrooms are randomly created on the grid excluding the
 *  player's screen boundary, they are created using the centre of each cell provided the
 *  cell is not occupied. Creation of one mushroom given a position only maps the position
 *  to a cell without querying it status.
 *  \author 1932442 Bophilo Ntsemi and 1839578 Masilo Sekhele
 *  \version 3.0
 */
class mushroomManager
{
    public:

        /** \fn mushroomManager(const ScreenParameters& Screen_Parameters);
         * \brief Parameterized constructor. Creates a mushroomManager object.
         *  \param grid of type Grid.
         */
        mushroomManager(const ScreenParameters& Screen_Parameters);

        /** \fn ~mushroomManager();
         * \brief Default Destructor. Destroys a mushrooms Class object.
         */
        ~mushroomManager();

        /** \fn shared_ptr<mushroomsClass> makeMushroom(positionHandler position);
         * \brief Generates a mushroom at the given position.
         *  \param position is of type positionHandler.
         *  \return shared_ptr<mushroomsClass>
         */
        shared_ptr<mushroomsClass> makeMushroom(positionHandler position);

        /** \fn  vector<shared_ptr<mushroomsClass>> makeMushrooms();
         * \brief Generates mushroomsClass.
         *  \return vector<shared_ptr<mushroomsClass>>
         */
        vector<shared_ptr<mushroomsClass>> makeMushrooms();

       /** \fn bool checkIfMushroomCanBeSpawn(positionHandler Position);
         * \brief Checks if a cell is occupied.
         *  \param position is of type positionHandler and contains position of the Flea.
         *  \return bool stating if the cell is occupied or not.
         */
        bool checkIfMushroomCanBeSpawn(positionHandler Position);

    protected:

    private:
        unsigned int  maxMushroom, maxColumn, maxRow;
        /**
        */
        const ScreenParameters ScreenParameters_;
        map<unsigned int, bool> cellIDList;

        /** \brief Maps the position into the defined rows and columns.
         *  \param position is of type positionHandler.
         *  \return positionHandler
         */
        positionHandler screenCoordinate(positionHandler position);

        /** \brief Maps the position into the defined X position and Y position.
         *  \param position is of type positionHandler.
         *  \return positionHandler
         */
        positionHandler LinkingCoordinates(positionHandler position);


        /** \fn bool checkIfCoordinateCellIsFilled(int x, int y);
         * \brief Checks if a cell is occupied.
         *  \param x is an int and contains the centre x position of a cell.
         *  \param y is an int and contains the centre y position of a cell.
         *  \return bool stating if the cell is occupied or not.
         */
        bool checkIfCoordinateCellIsFilled(int x, int y);

       /** \fn void RowAndColumn();
        * \brief Maps the grid into rows and columns (cells).
        */
        void RowAndColumn();

};
#endif // MUSHROOMMANAGER_H
