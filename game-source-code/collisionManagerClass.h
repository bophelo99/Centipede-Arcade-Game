#ifndef COLLISIONMANAGERCLASS_H
#define COLLISIONMANAGERCLASS_H
#include "entityBaseClass.h"
#include "entityMovementBaseClass.h"
#include "HashGrid.h"
#include "centipedeClass.h"
#include "SplitAxis.h"
#include "movingObjetsType.h"
/**
*/
#include <memory>
#include <algorithm>
#include <memory>
/**
*/
using std::find;
using std::copy_if;
using std::count_if;
using std::begin;
using std::end;
using std::vector;
using std::shared_ptr;
using std::dynamic_pointer_cast;

using entityMovementBaseClass_ptr = std::shared_ptr<entityMovementBaseClass>;


/**	\class collisionManagerClass
 * 	\brief A Logic Layer class that determines whether collisions have occurred
 * 	       between game objects. This class makes use of the algorithm implemented in
 *         SplitAxis class to check for overlap between two BoundaryHandler objects.
 *         Depending on which game objects are overlapping the appropriate behaviour is
 *         determined. This class aims to reduce collision checks by making use of the
 *         HashGrid class. The spatial grid hash is generated every time checkCollisions()
 *         gets called. While iterating through the movable objects, the Spatial grid Hash is
 *         used to retrieve any nearby objects in the cell an object is located in.
 *         Collision checks are then only performed between an object and the objects in the
 *         same cell location(s).
 *  \author 1932442 Bophilo Ntsemi and 1839578 Masilo Sekhele
 *  \version 3.0
 */

class collisionManagerClass
{
    public:

        /** \fn collisionManagerClass(const ScreenParameters& ScreenParameters_);
         * \brief Parameterized Constructor. Constructs a CollisionHandler object.
         *  \param grid is of type Grid and contains the screen width and height.
         */
        collisionManagerClass(const ScreenParameters& ScreenParameters_);

        /** \fn ~collisionManagerClass();
         * \brief Default Destructor. Destroys a Collision Handler object.
         */
        ~collisionManagerClass();

        /** \fn void detectEntitiesCollisions(vector<entityBaseClass_ptr>& gameobjects, vector<entityMovementBaseClass_ptr>& movingobjects);
         * \brief Checks for collisions between the game objects that are still alive.
         *
         *  \param game_objects is a vector of shared pointers of type entityBaseClass.
         *  \param moving_game_objects is a vector of shared pointers of type entityMovementBaseClass_ptr.
         */
        void detectEntitiesCollisions(vector<entityBaseClass_ptr>& gameobjects, vector<entityMovementBaseClass_ptr>& movingobjects);

        /** \fn int getPoints();
         * \brief Returns the points the player has obtained from killing game enemies.
         *  \return int
         */
        int getPoints();

    protected:

    private:
        int scorePoints;
        /**
        */
        SplitAxis SplitAxis_;
        HashGrid HashGrid_;

        /** \fn void DetectMushroomAndCentipedeCollision(vector<entityMovementBaseClass_ptr>& centipede);
         * \brief Checks collisions between a centipede and a Mushroom.
         *         If a collision occurs, the Centipede segment goes down and changes direction.
         *  \param centipede is a vector of shared pointers to entityMovementBaseClass objects of movingObjetsType::CENTIPEDE.
         */
        void DetectMushroomAndCentipedeCollision(vector<entityMovementBaseClass_ptr>& centipede);

        /** \fn void DetectBulletAndEnemiesCollision(vector<entityMovementBaseClass_ptr>& Bullets, vector<entityMovementBaseClass_ptr>& centipede);
         * \brief Checks whether a PlayerBullet collides with every other game object near it.
         *         If collisions occur both call their respective eliminated()
         *         functions. Mushroom will decrement its number of lives while others will set alive status false.
         *  \param player_bullets is a vector of shared pointers to entityMovementBaseClass objects of movingObjetsType::PLAYER_LASER_BULLET.
         *  \param centipede is a vector of shared pointers to entityMovementBaseClass objects of movingObjetsType::CENTIPEDE.
         */
        void DetectBulletAndEnemiesCollision(vector<entityMovementBaseClass_ptr>& Bullets, vector<entityMovementBaseClass_ptr>& centipede);

        /** \fn void DetectCentipedeAndCentipedeCollision(vector<entityMovementBaseClass_ptr>& centipede);
         * \brief Checks collisions between a centipede and a centipede.
         *         If a collision occurs, then both Centipedes go down or up and change their directions.
         *  \param centipede is a vector of shared pointers to entityMovementBaseClass objects of movingObjetsType::CENTIPEDE.
         */
        void DetectCentipedeAndCentipedeCollision(vector<entityMovementBaseClass_ptr>& centipede);

        /** \fn void DetectPlayerAndEntitiesCollision(vector<entityMovementBaseClass_ptr>& player);
         * \brief Checks collisions between a Player and other game objects.
         *         If a collision occurs, with a Mushroom the player's direction is set to NONE.
         *         If it's anything other than a Mushroom the player loses a life.
         *  \param player is a shared pointer to anentityMovementBaseClass object of movingObjetsType::PLAYER.
         */
        void DetectPlayerAndEntitiesCollision(vector<entityMovementBaseClass_ptr>& player);

       /** \fn void DetectScorpionAndMushroomCollision(vector<entityMovementBaseClass_ptr>& scorpions);
         * \brief Checks collisions between a Scorpion and Mushroom.
         *        If a collision occurs with a mushroom, the mushroom is set to poisoned.
         *  \param scorpions is a vector of shared pointer(s) to an entityMovementBaseClass object of movingObjetsType::SCORPION.
         */
        void DetectScorpionAndMushroomCollision(vector<entityMovementBaseClass_ptr>& scorpions);

       /** \fn void DetectSpiderAndMushroomCollision(vector<entityMovementBaseClass_ptr>& spiders);
         * \brief Checks collisions between a Spider and Mushroom.
         *        If a collision occurs with a mushroom, the mushroom is set to eliminated.
         *        Its alive status to becomes false.
         *  \param spiders vector of shared pointer(s) to an entityMovementBaseClass object of movingObjetsType::SPIDER.
         */
        void DetectSpiderAndMushroomCollision(vector<entityMovementBaseClass_ptr>& spiders);

        /** \fn void splitCentipede(vector<entityMovementBaseClass_ptr>& centipede, entityBaseClass_ptr& centi_segment);
         * \brief Updates the centipede train after a bullet has collided with a segment.
         *         Sets the next segment as a CentipedeClass::CentiBodyType::HEAD and updates
         *         the collision positions of the segments following the new head.
         *  \param centipede is a vector of shared pointers to entityMovementBaseClass objects of movingObjetsType::CENTIPEDE.
         *  \param centi_segment is a shared pointer to an entityBaseClass object of movingObjetsType::CENTIPEDE.
         */
        void splitCentipede(vector<entityMovementBaseClass_ptr>& centipede, entityBaseClass_ptr& centi_segment);

        /** \fn void modifyCentipede(vector<entityMovementBaseClass_ptr>& centipede,entityBaseClass_ptr centi_segment, positionHandler PointOFCollision, bool poisonedPos, bool shiftFromCollision);
          * \brief Updates the train behind a head that has collided with a Mushroom or another Centipede train.
         *  \param centipede is a vector of shared pointers to entityMovementBaseClass objects of movingObjetsType::CENTIPEDE.
         *  \param centi_segment is a shared pointer to an entityBaseClass object of type movingObjetsType::CENTIPEDE.
         *  \param PointOFCollision is a Position object and contains the position where a head has collided.
         *  \param poisonedPos is bool indicating whether the head collided with a poisoned mushroom.
         *  \param shiftFromCollision is a bool indicating whether the centipede train should be moved
                   to get out of a collision.
         */
        void modifyCentipede(vector<entityMovementBaseClass_ptr>& centipede,entityBaseClass_ptr centi_segment, positionHandler PointOFCollision, bool poisonedPos, bool shiftFromCollision);

        /**\fn int sumOfObjects(vector<entityMovementBaseClass_ptr>::iterator first, vector<entityMovementBaseClass_ptr>::iterator last, movingObjetsType movingObjetsType);
         *\brief Returns the number of objects of the specified object type in the
         *        range given.
         * \param first is a iterator to a vector of shared pointers of type entityMovementBaseClass.
         * \param last is a iterator to a vector of shared pointers of type entityMovementBaseClass.
         * \param movingObjetsType is of type enum class movingObjetsType.
         * \return int containing the number of objects.
         */
        int sumOfObjects(vector<entityMovementBaseClass_ptr>::iterator first, vector<entityMovementBaseClass_ptr>::iterator last, movingObjetsType movingObjetsType);

       /** \fn vector<entityMovementBaseClass_ptr> copyObjects(std::vector<entityMovementBaseClass_ptr>::iterator first, vector<entityMovementBaseClass_ptr>::iterator last, movingObjetsType movingObjetsType);
         * \brief Copies the objects from a vector of the specified object type in the
         *       range given to another vector.
         * \param first is a iterator to a vector of shared pointers of type entityMovementBaseClass.
         * \param last is a iterator to a vector of shared pointers of type entityMovementBaseClass.
         * \param movingObjetsType is of type enum class movingObjetsType.
         * \return vector<entityMovementBaseClass_ptr> containing the copied objects based on the object type.
         */
        vector<entityMovementBaseClass_ptr> copyObjects(std::vector<entityMovementBaseClass_ptr>::iterator first, vector<entityMovementBaseClass_ptr>::iterator last, movingObjetsType movingObjetsType);

};

#endif // COLLISIONMANAGERCLASS_H
