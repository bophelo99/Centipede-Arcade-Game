#include "timerClass.h"
#include <ctime>
using namespace std;
timerClass::timerClass()
:Time_start{0.0},
 Time_pause{0.0},
 Time_resume{0.0},
 Time_run{0.0},
 Time_lap{0.0},
 Time_stop{0.0},
 Timemode_{TimeMode::STOP}
{
    //ctor
}

void timerClass::resertTimer()
{
 Time_start = 0.0;
 Time_pause = 0.0;
 Time_resume = 0.0;
 Time_run = 0.0;
 Time_lap = 0.0;
 Time_stop = 0.0;
 Timemode_ = TimeMode::STOP;
}

void timerClass::Start()
{
   if(Timemode_ != TimeMode::RUN) Timemode_ = TimeMode::RUN;
   Time_start = GetProcessTime(); Time_run = 0.0f;
   return;
}

void timerClass::Pause()
{
   if(Timemode_ != TimeMode::PAUSE)Timemode_ = TimeMode::PAUSE;
   Time_pause = GetProcessTime();
   return;
}

void timerClass::Resume()
{
    if(Timemode_ == TimeMode::PAUSE){
        Timemode_ = TimeMode::RUN;
        Time_resume = GetProcessTime();
        Time_run -=(Time_resume - Time_pause);
        Time_lap +=(Time_resume - Time_pause);
    }
    return;
}

void timerClass::Stop()
{
     if(Timemode_ != TimeMode::STOP) Timemode_ = TimeMode::STOP;
     Time_stop = GetProcessTime();
    return;
}

double timerClass::getLapTime()
{
   if(Timemode_ != TimeMode::STOP || Timemode_ == TimeMode::PAUSE)
    Time_lap = GetProcessTime() - Time_lap;
   return Time_lap;
}

double timerClass::getPauseTime()
{
  return Time_pause;
}

double timerClass::getStopTime()
{
   Stop();
   return Time_stop-Time_start;
}

double timerClass::getRunTime()
{
   Time_run +=(Time_stop - Time_start);
   return Time_run;
}

double timerClass::GetProcessTime()
{
    clock_t time = clock();
    return static_cast<double>(time)/CLOCKS_PER_SEC;
}
