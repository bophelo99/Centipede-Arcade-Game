#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
/**
*/
#include "../game-source-code/resourcesManagerClass.h"
#include <vector>
/**
*/
#include <algorithm>
/**
*/
/**
  * The following tests test for the Resource Manager class
  *
  */
TEST_CASE("Test if the entity type and the resource directory path can be set and retrived")
{  //check player
   resourcesManagerClass::defineTypeOfResource resourceType = resourcesManagerClass::defineTypeOfResource::PLAYER;
   resourcesManagerClass resourceObject{resourceType, "resources/Player.png"};
   const std::string resourcePath = "resources/Player.png";
   CHECK(resourcePath == resourceObject.getresourceDirectoryPath());
   CHECK(resourceType == resourceObject.getresourceType());

   //check mushroom
   resourcesManagerClass::defineTypeOfResource resourceType1 = resourcesManagerClass::defineTypeOfResource::MUSHROOM;
   resourcesManagerClass resourceObject1{resourceType1, "resources/Mushroom.png"};
   const std::string resourcePath1 = "resources/Mushroom.png";
   CHECK(resourcePath1 == resourceObject1.getresourceDirectoryPath());
   CHECK(resourceType1 == resourceObject1.getresourceType());
}

TEST_CASE("Mushroom entity details are stored and can be accessed")
{
    resourcesManagerClass resources{}; resources.setResourceInfo();
    resourcesManagerClass::defineTypeOfResource  TypeOfResource =  resourcesManagerClass::defineTypeOfResource::MUSHROOM;
    auto iterator = std::find_if((resources.ResoucesDirectoryPath()).begin(), (resources.ResoucesDirectoryPath()).end(),
                            [&, TypeOfResource](const resourcesManagerClass& resource){
                                      return (resource.getresourceType()==TypeOfResource);
                            } );
    int ImageColumns=4, ImageRows=2;
    CHECK(std::get<0>(iterator->getResourceInfo()).at(0) == ImageRows);
    CHECK(std::get<0>(iterator->getResourceInfo()).at(1) == ImageColumns);
}

TEST_CASE("Player entity details are stored and can be accessed")
{
    resourcesManagerClass resources{}; resources.setResourceInfo();
    resourcesManagerClass::defineTypeOfResource  TypeOfResource =  resourcesManagerClass::defineTypeOfResource::PLAYER;
    auto iterator = std::find_if((resources.ResoucesDirectoryPath()).begin(), (resources.ResoucesDirectoryPath()).end(),
                            [&, TypeOfResource](const resourcesManagerClass& resource){
                                      return (resource.getresourceType()==TypeOfResource);
                            } );
    int ImageColumns=1, ImageRows=1;
    CHECK(std::get<0>(iterator->getResourceInfo()).at(0) == ImageRows);
    CHECK(std::get<0>(iterator->getResourceInfo()).at(1) == ImageColumns);
}

TEST_CASE("PLayerBullet entity details are stored and can be accessed")
{
    resourcesManagerClass resources{}; resources.setResourceInfo();
    resourcesManagerClass::defineTypeOfResource  TypeOfResource =  resourcesManagerClass::defineTypeOfResource::BULLET;
    auto iterator = std::find_if((resources.ResoucesDirectoryPath()).begin(), (resources.ResoucesDirectoryPath()).end(),
                            [&, TypeOfResource](const resourcesManagerClass& resource){
                                      return (resource.getresourceType()==TypeOfResource);
                            } );
    int ImageColumns=1, ImageRows=1;
    CHECK(std::get<0>(iterator->getResourceInfo()).at(0) == ImageRows);
    CHECK(std::get<0>(iterator->getResourceInfo()).at(1) == ImageColumns);
}

TEST_CASE("Centipede entity details are stored and can be accessed")
{
    resourcesManagerClass resources{}; resources.setResourceInfo();
    resourcesManagerClass::defineTypeOfResource  TypeOfResource =  resourcesManagerClass::defineTypeOfResource::CENTIPEDE;
    auto iterator = std::find_if((resources.ResoucesDirectoryPath()).begin(), (resources.ResoucesDirectoryPath()).end(),
                            [&, TypeOfResource](const resourcesManagerClass& resource){
                                      return (resource.getresourceType()==TypeOfResource);
                            } );
    int ImageColumns=8, ImageRows=2;
    CHECK(std::get<0>(iterator->getResourceInfo()).at(0) == ImageRows);
    CHECK(std::get<0>(iterator->getResourceInfo()).at(1) == ImageColumns);
}

TEST_CASE("Scorpion entity details are stored and can be accessed")
{
    resourcesManagerClass resources{}; resources.setResourceInfo();
    resourcesManagerClass::defineTypeOfResource  TypeOfResource =  resourcesManagerClass::defineTypeOfResource::SCORPION;
    auto iterator = std::find_if((resources.ResoucesDirectoryPath()).begin(), (resources.ResoucesDirectoryPath()).end(),
                            [&, TypeOfResource](const resourcesManagerClass& resource){
                                      return (resource.getresourceType()==TypeOfResource);
                            } );
    int ImageColumns=4, ImageRows=1;
    CHECK(std::get<0>(iterator->getResourceInfo()).at(0) == ImageRows);
    CHECK(std::get<0>(iterator->getResourceInfo()).at(1) == ImageColumns);
}

TEST_CASE("Spider entity details are stored and can be accessed")
{
    resourcesManagerClass resources{}; resources.setResourceInfo();
    resourcesManagerClass::defineTypeOfResource  TypeOfResource =  resourcesManagerClass::defineTypeOfResource::SPIDER;
    auto iterator = std::find_if((resources.ResoucesDirectoryPath()).begin(), (resources.ResoucesDirectoryPath()).end(),
                            [&, TypeOfResource](const resourcesManagerClass& resource){
                                      return (resource.getresourceType()==TypeOfResource);
                            } );
    int ImageColumns=8, ImageRows=2;
    CHECK(std::get<0>(iterator->getResourceInfo()).at(0) == ImageRows);
    CHECK(std::get<0>(iterator->getResourceInfo()).at(1) == ImageColumns);
}

TEST_CASE("Flea entity details are stored and can be accessed")
{
    resourcesManagerClass resources{}; resources.setResourceInfo();
    resourcesManagerClass::defineTypeOfResource  TypeOfResource =  resourcesManagerClass::defineTypeOfResource::FLEA;
    auto iterator = std::find_if((resources.ResoucesDirectoryPath()).begin(), (resources.ResoucesDirectoryPath()).end(),
                            [&, TypeOfResource](const resourcesManagerClass& resource){
                                      return (resource.getresourceType()==TypeOfResource);
                            } );
    int ImageColumns=16, ImageRows=2;
    CHECK(std::get<0>(iterator->getResourceInfo()).at(0) == ImageRows);
    CHECK(std::get<0>(iterator->getResourceInfo()).at(1) == ImageColumns);
}

TEST_CASE("DDT_BOMBS entity details are stored and can be accessed")
{
    resourcesManagerClass resources{}; resources.setResourceInfo();
    resourcesManagerClass::defineTypeOfResource  TypeOfResource =  resourcesManagerClass::defineTypeOfResource::DDT_BOMBS;
    auto iterator = std::find_if((resources.ResoucesDirectoryPath()).begin(), (resources.ResoucesDirectoryPath()).end(),
                            [&, TypeOfResource](const resourcesManagerClass& resource){
                                      return (resource.getresourceType()==TypeOfResource);
                            } );
    int ImageColumns=32, ImageRows=3;
    auto[Image, direction] = iterator->getResourceInfo();
    CHECK(Image[0] == ImageRows);
    CHECK(Image[1] == ImageColumns);
}
