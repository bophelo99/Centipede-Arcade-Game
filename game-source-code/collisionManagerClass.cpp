#include "collisionManagerClass.h"
#include <cmath>
collisionManagerClass::collisionManagerClass(const ScreenParameters& ScreenParameters_)
: scorePoints{0},
  HashGrid_{ScreenParameters_}
{
    //ctor
}

void collisionManagerClass::detectEntitiesCollisions(std::vector<entityBaseClass_ptr>& gameobjects, std::vector<entityMovementBaseClass_ptr>& movingobjects)
{
    HashGrid_.constructSpatialGrid(gameobjects);
    auto playerBullets = copyObjects(movingobjects.begin(), movingobjects.end(), movingObjetsType::BULLET);
    auto centipede = copyObjects(movingobjects.begin(), movingobjects.end(), movingObjetsType::CENTIPEDE);
    auto player = copyObjects(movingobjects.begin(), movingobjects.end(), movingObjetsType::PLAYER);
    auto scorpion = copyObjects(movingobjects.begin(), movingobjects.end(), movingObjetsType::SCORPION);
    auto spider = copyObjects(movingobjects.begin(), movingobjects.end(), movingObjetsType::SPIDER);
    ///
    DetectPlayerAndEntitiesCollision(player);
    DetectBulletAndEnemiesCollision(playerBullets, centipede);
    DetectCentipedeAndCentipedeCollision(centipede);
    DetectMushroomAndCentipedeCollision(centipede);
    DetectScorpionAndMushroomCollision(scorpion);
    DetectSpiderAndMushroomCollision(spider);
    HashGrid_.remove();
}

int collisionManagerClass::getPoints()
{
   auto point = scorePoints; scorePoints=0;
   return point;
}

void collisionManagerClass::DetectMushroomAndCentipedeCollision(vector<entityMovementBaseClass_ptr>& centipede)
{
   for(auto& segment: centipede)
   {
       auto centi_heat_ptr = dynamic_pointer_cast<centipedeClass>(segment);
       if(segment->isAlive() && centi_heat_ptr->getCentiBodyType()== CentiBodyType::HEAD && !segment->isPoisoned())
       {
          auto nearobjects = HashGrid_.DetectNearObjects(segment);
          for(auto& object : nearobjects)
          {
              if(object->isAlive() && object->getObjectType()== movingObjetsType::MUSHROOM)
              {
                  if(SplitAxis_.checkOverlap(segment->getBoundary(), object->getBoundary()))
                  {
                      auto moveOutOFcollision=false;
                      modifyCentipede(centipede, segment, centi_heat_ptr->getPosition(), object->isPoisoned(), moveOutOFcollision);
                      if(object->isPoisoned()) segment->poison();
                      else centi_heat_ptr->switchDirection();
                  }
              }
          }
       }
   }
}

void collisionManagerClass::DetectBulletAndEnemiesCollision(std::vector<entityMovementBaseClass_ptr>& Bullets, std::vector<entityMovementBaseClass_ptr>& centipede)
{
   for(auto& bullet: Bullets)
   {
       auto nearobjects = HashGrid_.DetectNearObjects(bullet);
       for(auto& object: nearobjects)
       {
           if(!bullet->isAlive()) break;
           if(object->getObjectType() != movingObjetsType::PLAYER && object->getObjectType()!= movingObjetsType::BULLET && object->isAlive())
           {
               if(SplitAxis_.checkOverlap(bullet->getBoundary(), object->getBoundary()))
               {
                   bullet->eliminated();
                   object->eliminated();
                   scorePoints+=object->getPoints();
                   if(object->getObjectType() == movingObjetsType::CENTIPEDE)
                    splitCentipede(centipede, object);
               }
           }
       }
   }
}

void collisionManagerClass::DetectCentipedeAndCentipedeCollision(vector<entityMovementBaseClass_ptr>& centipede)
{
   for(auto& segment: centipede)
   {
       auto centi_heat_ptr = dynamic_pointer_cast<centipedeClass>(segment);
       if(segment->isAlive() && !segment->isPoisoned() && centi_heat_ptr->getCentiBodyType()==CentiBodyType::HEAD)
       {
           auto nearobjects = HashGrid_.DetectNearObjects(segment);
           for(auto& object : nearobjects)
           {
              if(object->isAlive() && object->getObjectType()== movingObjetsType::CENTIPEDE)
              {
                 if(SplitAxis_.checkOverlap(segment->getBoundary(), object->getBoundary()))
                 {
                     auto poisonedCollision= false;
                     auto moveOutOfCollision = true;
                     modifyCentipede(centipede, segment, centi_heat_ptr->getPosition(), poisonedCollision, moveOutOfCollision);
                     centi_heat_ptr->switchDirection();
                     centi_heat_ptr->move();
                 }
              }
           }
       }
   }
}

void collisionManagerClass::DetectPlayerAndEntitiesCollision(vector<entityMovementBaseClass_ptr>& player)
{
    for(auto& player_: player)
    {
       auto nearObjects = HashGrid_.DetectNearObjects(player_);
       for(auto& object: nearObjects)
       {
           if(!player_->isAlive()) return;
           if(SplitAxis_.checkOverlap(player_->getBoundary(), object->getBoundary()))
           {
               if(object->getObjectType()==movingObjetsType::MUSHROOM)
               {
                   objectsDirection direcion;
                   if(player_->getDirection()==objectsDirection::UP) direcion = objectsDirection::DOWN;
                   else if(player_->getDirection()==objectsDirection::DOWN) direcion = objectsDirection::UP;
                   else if(player_->getDirection()==objectsDirection::LEFT) direcion = objectsDirection::RIGHT;
                   else if(player_->getDirection()==objectsDirection::RIGHT) direcion = objectsDirection::LEFT;

                   //mover player
                   player_->setDirection(direcion);
                   player_->move(); player_->move();
                   player_->setDirection(objectsDirection::NONE);

               }
               else
               {
                   object->eliminated();
                   player_->eliminated();
                   return;
               }
           }
       }
    }
}

void collisionManagerClass::DetectScorpionAndMushroomCollision(vector<entityMovementBaseClass_ptr>& scorpions)
{
  for(auto& scorpion :scorpions)
   {
       if(scorpion->isAlive())
       {
          auto nearobjects = HashGrid_.DetectNearObjects(scorpion);
          for(auto& object: nearobjects)
          {
              if(object->isAlive() && object->getObjectType()==movingObjetsType::MUSHROOM)
              {
                 if(SplitAxis_.checkOverlap(scorpion->getBoundary(), object->getBoundary()))
                    object->poison();
              } //if
          } // for
       }//if
   }
}

void collisionManagerClass::DetectSpiderAndMushroomCollision(vector<entityMovementBaseClass_ptr>& spiders)
{
      for(auto& spider :spiders)
   {
       if(spider->isAlive())
       {
          auto nearobjects = HashGrid_.DetectNearObjects(spider);
          for(auto& object: nearobjects)
          {
              if(object->isAlive() && object->getObjectType()==movingObjetsType::MUSHROOM)
              {
                 if(SplitAxis_.checkOverlap(spider->getBoundary(), object->getBoundary()))
                    while(object->isAlive()) object->eliminated();
              } //if
          } // for
       }//if
   }
}

void collisionManagerClass::splitCentipede(vector<entityMovementBaseClass_ptr>& centipede, entityBaseClass_ptr& centi_segment)
{
   auto newHead_iterator = find(centipede.begin(), centipede.end(), centi_segment);
        newHead_iterator = find_if(newHead_iterator, centipede.end(), [](const entityMovementBaseClass_ptr& object)
                                                                           {
                                                                               return (object->isAlive());
                                                                           });
       if(newHead_iterator!=centipede.end())
       {
          auto centi_seg_iter = dynamic_pointer_cast<centipedeClass>(*newHead_iterator);
          centi_seg_iter->setCentiBodyType(CentiBodyType::HEAD);
          auto Ypos_newHead = centi_seg_iter->getPosition().getY_position();
          auto centi__segment_iterator = find(centipede.begin(), centipede.end(), *newHead_iterator);
          for(++centi__segment_iterator; centi__segment_iterator!= centipede.end(); ++centi__segment_iterator)
          {
              auto centi_new_iter = dynamic_pointer_cast<centipedeClass>(*centi__segment_iterator);
              if(centi_new_iter->getCentiBodyType() == CentiBodyType::HEAD) break;
              if(centi_new_iter->isAlive() && centi_new_iter->getPosition().getY_position()==Ypos_newHead)
                centi_new_iter->remove_if_HeadCollisions();
          }
       }
}

void collisionManagerClass::modifyCentipede(vector<entityMovementBaseClass_ptr>& centipede,entityBaseClass_ptr centi_segment, positionHandler PointOFCollision, bool poisonedPos, bool shiftFromCollision)
{
    auto centi_segment_iter = find(centipede.begin(), centipede.end(), centi_segment);
    for(++centi_segment_iter; centi_segment_iter!=centipede.end(); ++centi_segment_iter)
    {
       auto centi_segment_ptr = dynamic_pointer_cast<centipedeClass>(*centi_segment_iter);
       if(centi_segment_ptr->getCentiBodyType() == CentiBodyType::HEAD) break;
       if(centi_segment_ptr->isAlive())
       {
          centi_segment_ptr->store_collision(PointOFCollision, poisonedPos);
          if(shiftFromCollision)
            centi_segment_ptr->move();
       }
    }
}

int collisionManagerClass::sumOfObjects(vector<entityMovementBaseClass_ptr>::iterator first, vector<entityMovementBaseClass_ptr>::iterator last, movingObjetsType objectType)
{
    return (count_if(first, last, [&, objectType](const entityMovementBaseClass_ptr& object)
                                                  {
                                                      return (object->getObjectType()==objectType);
                                                  }));
}

vector<entityMovementBaseClass_ptr> collisionManagerClass::copyObjects(vector<entityMovementBaseClass_ptr>::iterator first, std::vector<entityMovementBaseClass_ptr>::iterator last, movingObjetsType objectType)
{
   auto Totobjects = sumOfObjects(first, last, objectType);
   vector<entityMovementBaseClass_ptr> copyElem(Totobjects);
   copy_if(first, last, copyElem.begin(), [&, objectType](const entityMovementBaseClass_ptr& object)
                                                  {
                                                      return (object->getObjectType()==objectType);
                                                  });
   return copyElem;
}

collisionManagerClass::~collisionManagerClass()
{
    //dtor
}
