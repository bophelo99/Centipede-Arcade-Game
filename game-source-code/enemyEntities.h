#ifndef ENEMYENTITIES_H
#define ENEMYENTITIES_H
/**
*/
#include "centipedeClass.h"
#include "timerClass.h"
#include "mushroomManager.h"
#include "Spider.h"
#include "ScorpionClass.h"
#include "flea.h"
/**
*/
#include <ctime>
#include <vector>
#include <memory>
using std::vector;
using std::shared_ptr;
using std::make_shared;

/** \class enemyEntities
 *  \brief This class is used to creates all the enemy objects of the game.
 *         It periodically creates Spider objects after a specified delay. It generates
 *         the initial Centipede train that is used in the beginning of the game. It can
 *         also generate a specified number CentipedeSegment of CentiBodyType::HEAD periodically.
 *  \author 1932442 Bophilo Ntsemi and 1839578 Masilo Sekhele
 *  \version 3.0
 */

class enemyEntities
{
    public:
        /** \fn enemyEntities(const ScreenParameters& Screen_Parameters_);
         * \brief Parameterized constructor. Creates an EnemyFactory object.
         *  \param grid of type Grid.
         */
        enemyEntities(const ScreenParameters& Screen_Parameters_);

        /** \fn ~enemyEntities();
         * \brief Destroys a EnemyFactory object.
         */
        ~enemyEntities();

         /** \fn vector < shared_ptr<centipedeClass>> generateCentipedeHeads(int heads);
          * \brief Generates centipede heads.
         *  \param heads is an int containing the number of heads to be generated.
         *  \return vector<shared_ptr<centipedeClass>>>
         */
        vector < shared_ptr<centipedeClass>> generateCentipedeHeads(int heads);

       /** \fn vector < shared_ptr<centipedeClass>> generateCentipede();
         * \brief Generates a Centipede made up of centipede segments.
         * \return vector<shared_ptr<centipedeClass>>
         */
        vector < shared_ptr<centipedeClass>> generateCentipede();

        /** \fn vector < shared_ptr<Spider>> generateASpider();
         * \brief Generates a spider periodically.
         *  \return vector<shared ptr<Spider>>
         */
        vector < shared_ptr<Spider>> generateASpider();

        /** \fn vector < shared_ptr<Scorpion>> generateAScorpion();
         * \brief Generates a scorpion at a random position.
         *  \return vector<shared ptr<Scorpion>>
         */
        vector < shared_ptr<Scorpion>> generateAScorpion();

        /** \fn vector < shared_ptr<flea>> generateAFlea();
         * \brief Generates A flea periodically.
         *  \return vector<shared ptr<Spider>>
         */
        vector < shared_ptr<flea>> generateAFlea();

         /** \fn double getSpiderReleaseTime() const;
          * \brief Returns the current delay of the timer.
         *  \return double
         */
        double getSpiderReleaseTime() const;

        /** \fn double getFleaReleaseTime() const;
         * \brief Returns the current delay of the timer.
         *  \return double
         */
        double getFleaReleaseTime() const;

        /** \fn double getCentipedeHeadsReleaseTime() const;
         * \brief Returns the current delay of the timer.
         *  \return double
         */
        double getCentipedeHeadsReleaseTime() const;

        /** \fn void setCentipedeHeadsReleaseTime(double new_delay);
         * \brief Sets the Centipede heads release time delay.
         *  \param new_delay is a double containing the new delay for the Centipede
         *         heads generation.
         */
        void setCentipedeHeadsReleaseTime(double new_delay);

        /** \fn void setSpiderReleaseTime(double new_delay);
         * \brief Sets the Spider release time delay.
         *  \param new_delay is a double containing the new delay for the Spider generation.
         */
        void setSpiderReleaseTime(double new_delay);

        /** \fn void setFleaReleaseTime(double new_delay);
         * \brief Sets the Flea release time delay.
         *  \param new_delay is a double containing the new delay for the Flea generation.
         */
        void setFleaReleaseTime(double new_delay);

        /** \fn void resetEntities();
         * \brief Resets states of generated objects to false.
         */
        void resetEntities();

    protected:
        /**
        */


    private:
        /**
        */
        const ScreenParameters ScreenParameters_;
        CentipedeDimension centipedeDimension_;
        /**
        */
        bool IfCentipedeGenerated;
        bool ifCentipedeHeadsGenerated;
        bool IFScorpionGenerated;
        /**
        */
        timerClass centipedetimer_;
        double headReleaseTime, headLastReleaseTime;
        /**
        */
        timerClass spidertimer_;
        double spiderReleaseTime, spiderLastReleaseTime;
      /**
        */
        timerClass Fleatimer_;
        double FleaReleaseTime, FleaLastReleaseTime;

};

#endif // ENEMYENTITIES_H
