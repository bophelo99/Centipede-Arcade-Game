#ifndef RESOURCESMANAGERCLASS_H
#define RESOURCESMANAGERCLASS_H
/**
*/
#include "objectsDirection.h"
/**
*/
#include <string>
#include <vector>
#include <map>
#include <tuple>
/**
*/
using std::string;
using std::vector;
using std::map;
using std::pair;
using std::tuple;

/** \class resourcesManagerClass
 *  \brief A data layer class containing a AssetType and the path to the asset. Loads
 *         the assets (textures, fonts, sounds) used by the game objects. This class also stores
 *         details about the number of images in the game textures and the direction
 *         objects face in the texture if any.
 *  \author 1932442 Bophilo Ntsemi and 1839578 Masilo Sekhele
 *  \version 3.0
 */

class resourcesManagerClass
{
    public:
        /** \fn resourcesManagerClass();
         * \brief resourcesManagerClass() - Default Class Constructor.
		 */
        resourcesManagerClass();

       /** \fn enum class defineTypeOfResource
         * \enum defineTypeOfResource
         *  \brief A strongly typed enum class that contains the different game assets.
         */
        enum class defineTypeOfResource
        {
            FONT = 0,                   /** the  font used for text messages.*/
            SHOOTING_SOUND,             /** the sound used for bullets fired.*/
            LEVEL_UP_SOUND,             /** the sound used for Levelling up.*/
            MUSHROOM_REGENARATED_SOUND, /** the sound used for Mushroom regeneration.*/
            SCORPION_MOVING_SOUND,      /** the sound used for Scorpion movement.*/
            SPIDER_MOVING_SOUND,        /** the sound used for Spider movement.*/
            FLEA_MOVING_SOUND,          /** the sound used for Flea movement.*/
            PLAYER,         /** the texture used for a Player object.*/
            BULLET,         /** the texture used for a PlayerBullet object.*/
            CENTIPEDE,      /** the texture used for a CentipedeSegment object.*/
            MUSHROOM,       /** the texture used for a Mushroom object.*/
            SCORPION,       /** the texture used for a Scorpion object.*/
            SPIDER,         /** the texture used for a Spider object.*/
            FLEA            /** the texture used for a Flea object.*/
        };

        /** \fn resourcesManagerClass(defineTypeOfResource resourceType, string resourceDirectoryPath);
         * \brief Parameterized Constructor. Creates an resourcesManagerClass object.
		 *	       Used to create an resource Manager object containing the type
		 *	       of asset being loaded and the path where to find the asset.
		 *	\param resourceType is of type v and contains the type of asset being loaded.
		 *	\param resourceDirectoryPath is of type std::string and contains the path to the asset being loaded.
		 */
        resourcesManagerClass(defineTypeOfResource resourceType, string resourceDirectoryPath);

         /** \fn vector<resourcesManagerClass> ResoucesDirectoryPath();
          *\brief Returns a vector of type resourcesManagerClass containing
         *         all the asset information for the project.
         * 	\return vector<resourcesManagerClass>
         */
        vector<resourcesManagerClass> ResoucesDirectoryPath();

        /** \fn defineTypeOfResource getresourceType() const;
         * \brief Returns the defineTypeOfResource related to the resourcesManagerClass.
         * 	\return resourceType_ enum a strongly typed enumeration of defineTypeOfResource.
         */
        defineTypeOfResource getresourceType() const;

        /** \fn string getresourceDirectoryPath() const;
         * \brief Returns the path on the disk related to the asset.
         * 	\return string with path to the asset.
         */
        string getresourceDirectoryPath() const;

        /** \fn static void setResourceInfo();
         *	\brief Populates the map used to store the rows, columns and the default
         *         direction that images face in the texture for each game object. It is
         *         a static function because the map being updated is a static private member.
         */
        static void setResourceInfo();

       /** \fn tuple<vector<unsigned int>, objectsDirection> getResourceInfo() const;
         *	\brief Returns a tuple with a vector of type unsigned int containing
         *         the rows and columns in an image and a direction enum which gives
         *         information about the direction images face in the texture.
         * 	\return tuple<vector<unsigned int>, objectsDirection>
         */
        tuple<vector<unsigned int>, objectsDirection> getResourceInfo() const;

    protected:


    private:
            string resourceDirectoryPath_;         /** A string variable holding the directory path to the resources.*/
            defineTypeOfResource resourceType_;    /** A variable of type enum class defineTypeOfResource which Determines the type of resource.*/

            /**  A static map that holds the rows, columns and default direction in an image for each texture.
            */
            static map<defineTypeOfResource, tuple<vector<unsigned int>,objectsDirection >> TextureInfo;

            /** \fn static void storeResourceInfo(defineTypeOfResource resource, objectsDirection Direction, unsigned int numberOfRows, unsigned int NumberOFColumns);
             *	\brief A private static function that helps loadTextureDetails().
             *         Takes in the necessary inputs to be saved into the static private map
             *         called  TextureInfo.
             *  \param resource is of type defineTypeOfResource.
             *  \param numberOfRows is an int containing the rows in an image.
             *  \param NumberOFColumns is an int containing the columns in an image.
             *  \param direction is an objectsDirection enum containing the default direction faced in an image.
            */
            static void storeResourceInfo(defineTypeOfResource resource, objectsDirection Direction, unsigned int numberOfRows, unsigned int NumberOFColumns);
};

#endif // RESOURCESMANAGERCLASS_H
