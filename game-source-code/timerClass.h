#ifndef TIMERCLASS_H
#define TIMERCLASS_H

/**	\class timerClass
 *	\brief This class models a Stopwatch and returns time values in seconds.
 *  \author 1932442 Bophilo Ntsemi and 1839578 Masilo Sekhele
 *  \version 3.0
 */

class timerClass
{
    public:
        // Constructor:
	   /**\fn timerClass();
	    * \brief Default Constructor. Creates a Stopwatch object.
	    */
        timerClass();

        /**\fn void Start();
         * \brief Starts the timer.
        */
        void Start();

        /** \brief Pauses the stopwatch.
	    */
        void Pause();

        /** \fn void Resume();
        * \brief Resumes the stopwatch.
	    */
        void Resume();

        /** \fn void Stop();
        * \brief Stops the timer and resets.
	    */
        void Stop();

        /**\fn  void resertTimer();
         * \brief set all the TimerClass variables to the initial values.
	    */
        void resertTimer();

        /** \fn double getLapTime();
         * \brief Returns the value of time in seconds that has passed in the piece of code.
         *  \return double
        */
        double getLapTime();

        /** \fn double  getPauseTime();
         * \brief Returns the value time in seconds between start() and pause().
	     *  \return double
	    */
        double  getPauseTime();

         /** \fn double getStopTime();
          * \brief Returns the value time in seconds when stop is called.
	      *  \return double
	     */
        double getStopTime();

        /** \fn double getRunTime();
         * \brief Returns the value of time in seconds that has passed in the piece of code.
	     *  \return double
	    */
        double getRunTime();

        /** \fn v
          * \brief Returns the a time value in seconds at the point it is called.
	    *	\return double
	    */
        double GetProcessTime();

        /** \fn enum class TimeMode
         *  \enum Mode
	    *	\brief Strongly typed enum containing stopwatch operations.
	   */
        enum class TimeMode
        {
            RUN,    /** Indicates the StopWatch object as running.*/
            PAUSE,  /** Indicates the StopWatch object as paused.*/
            STOP    /** Indicates the StopWatch object as stopped.*/
        };

    protected:

    private:
        /**
        */
        double Time_start;
        double Time_pause;
        double Time_resume;
        double Time_run;
        double Time_lap;
        double Time_stop;

        /**  //Stores current state of stop watch:
        */
        TimeMode Timemode_;
};
#endif // TIMERCLASS_H
