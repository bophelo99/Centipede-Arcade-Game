#include "enemyEntities.h"

enemyEntities::enemyEntities(const ScreenParameters& Screen_Parameters_)
:ScreenParameters_{Screen_Parameters_},
 IfCentipedeGenerated{false},
 ifCentipedeHeadsGenerated{false},
 IFScorpionGenerated{false},
 headReleaseTime{7.5},
 headLastReleaseTime{0},
 spiderReleaseTime{15.0},
 spiderLastReleaseTime{0},
 FleaReleaseTime{22.5},
 FleaLastReleaseTime{0}

{
    //ctor
    srand(time(0));
}

enemyEntities::~enemyEntities()
{
    //dtor
}

vector < shared_ptr<centipedeClass>> enemyEntities::generateCentipedeHeads(int heads)
{
    vector <shared_ptr<centipedeClass>> Centi_Heads;
    auto YstartPos = ScreenParameters_.getheight()-((centipedeDimension_.width+2.0f)*7.5f);
    auto direction_right=true;
    if(!ifCentipedeHeadsGenerated){
        centipedetimer_.Pause();
        auto ElapsTime = centipedetimer_.getPauseTime();
        if((ElapsTime-headLastReleaseTime)>headReleaseTime)
        {
            for(auto index=0; index<heads; index++)
            {
                auto direction = objectsDirection::RIGHT;
                auto XstartPos= centipedeDimension_.width/2.0f;
                if(!direction_right)
                {
                    direction = objectsDirection::LEFT;
                    XstartPos = ScreenParameters_.getwidth()-centipedeDimension_.width/2.0f;
                }
               YstartPos +=(centipedeDimension_.height+2.0f);
                auto centipede_ptr = make_shared<centipedeClass>(ScreenParameters_, CentiBodyType::HEAD, positionHandler{XstartPos, YstartPos}, direction);
                Centi_Heads.push_back(centipede_ptr);
                direction_right = !direction_right;
            }
            headLastReleaseTime = ElapsTime;
            IfCentipedeGenerated = true;
        }
        centipedetimer_.Resume();
    }
    return Centi_Heads;
}

vector < shared_ptr<centipedeClass>> enemyEntities::generateCentipede()
{
    vector<shared_ptr<centipedeClass>> centipede;
    //
    if(!IfCentipedeGenerated){
            auto halfConst = 2.0f;
            auto halfWidth = (ScreenParameters_.getwidth()/halfConst) - centipedeDimension_.speed;
            auto direction = static_cast<objectsDirection>(rand()%2 + 2);
            //auto direction = objectsDirection::DOWN;
            auto centi_head = make_shared<centipedeClass>(ScreenParameters_, CentiBodyType::HEAD, positionHandler{halfWidth, -8.0f}, direction);
            centipede.push_back(centi_head);
            auto head_direction = centi_head->getDirection();
            auto InitialX_position = centi_head->getPosition().getX_position();
            auto numbeOfCentipedeSegment = 10;
            for(auto index=1; index<numbeOfCentipedeSegment; index++)
            {
                if(head_direction == objectsDirection::RIGHT)
                    InitialX_position -= (centipedeDimension_.width+1);
                else if (head_direction == objectsDirection::LEFT)
                    InitialX_position += (centipedeDimension_.width+1);

                auto centi_segment = make_shared<centipedeClass>(ScreenParameters_, CentiBodyType::BODY, positionHandler{InitialX_position, -8.0f}, head_direction);
                centipede.push_back(centi_segment);
            }
         IfCentipedeGenerated = true;
    }
    return centipede;
}

vector < shared_ptr<Spider>> enemyEntities::generateASpider()
{
    vector<shared_ptr<Spider>> spider;
    spidertimer_.Pause();
    auto time_elapsed = spidertimer_.getPauseTime();
    if((time_elapsed-spiderLastReleaseTime)>spiderReleaseTime)
    {
        auto spider_ptr = make_shared<Spider>(ScreenParameters_);
        spider.push_back(spider_ptr);

        spiderLastReleaseTime = time_elapsed;
    }
    spidertimer_.Resume();
    return spider;
}

vector < shared_ptr<flea>> enemyEntities::generateAFlea()
{
    vector<shared_ptr<flea>> fleas;

     Fleatimer_.Pause();
     auto time_elapsed = Fleatimer_.getPauseTime();
    if((time_elapsed-FleaLastReleaseTime)>FleaReleaseTime)
    {
        auto flea_ptr = make_shared<flea>(ScreenParameters_);
        fleas.push_back(flea_ptr);
        FleaLastReleaseTime = time_elapsed;
    }
    Fleatimer_.Resume();

    return fleas;
}

vector <shared_ptr<Scorpion>> enemyEntities::generateAScorpion()
{
    vector<shared_ptr<Scorpion>> scorpions;
    if(!IFScorpionGenerated)
    {
        scorpions.push_back(make_shared<Scorpion>(ScreenParameters_));
        IFScorpionGenerated= true;
    }
    return scorpions;
}

double enemyEntities::getSpiderReleaseTime() const
{
    return spiderReleaseTime;
}

double enemyEntities::getCentipedeHeadsReleaseTime() const
{
    return headReleaseTime;
}

double enemyEntities::getFleaReleaseTime() const
{
    return FleaReleaseTime;
}

void enemyEntities::setCentipedeHeadsReleaseTime(double new_delay)
{
    headReleaseTime=new_delay;
}

void enemyEntities::setSpiderReleaseTime(double new_delay)
{
    spiderReleaseTime=new_delay;
}

void enemyEntities::setFleaReleaseTime(double new_delay)
{
   FleaReleaseTime=new_delay;
}

void enemyEntities::resetEntities()
{
   IfCentipedeGenerated = false;
   IFScorpionGenerated = false;
   ifCentipedeHeadsGenerated =false;
   spiderLastReleaseTime=spidertimer_.GetProcessTime();
   headLastReleaseTime=centipedetimer_.getPauseTime();
   FleaLastReleaseTime=Fleatimer_.GetProcessTime();
   spidertimer_.Stop();
   centipedetimer_.Stop();
   Fleatimer_.Stop();
   spidertimer_.Start();
   centipedetimer_.Start();
   Fleatimer_.Start();
}
