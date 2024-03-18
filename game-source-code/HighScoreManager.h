#ifndef HIGHSCOREMANAGER_H
#define HIGHSCOREMANAGER_H

#include <string>
#include <fstream>

using std::string;
using std::ios;
using std::fstream;

/** \class HighScoreManager
 *  \brief A class that reads and writes the high score to a textfile.
 *  \author 1932442 Bophilo Ntsemi and 1839578 Masilo Sekhele
 *  \version 3.0
 */

class HighScoreManager
{
    public:

        /** \fn HighScoreManager();
         * \brief Default Constructor. Creates HighScoreManger object.
         */
        HighScoreManager();

        /** \fn int getHighScore();
         * \brief Returns the high score of the game.
         *  \return int
         */
        int getHighScore();

        /** \fn  void setHighScore(int score);
         * \brief Sets the high score of the game.
         *  \param score is of type int.
         *  \return void
         */
        void setHighScore(int score);

         /** \fn ~HighScoreManager();
          * \brief Default Destructor. Destroys HighScoreManger object.
          */
        ~HighScoreManager();

    private:
        int highScore_;		/**< An int variable that holds the high score.*/
        fstream file_; 		/**< A variable that holds the text file.*/
        string filePath_;	/**< A variable that holds the path to the text file.*/
};

#endif // HIGHSCOREMANAGER_H
