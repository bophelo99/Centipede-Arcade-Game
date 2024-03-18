#include "resourcesManagerClass.h"
map<resourcesManagerClass::defineTypeOfResource, tuple<vector<unsigned int>, objectsDirection >> resourcesManagerClass::TextureInfo;
resourcesManagerClass::resourcesManagerClass()
{
    //ctor
}

resourcesManagerClass::resourcesManagerClass(defineTypeOfResource resourceType, string resourceDirectoryPath)
: resourceDirectoryPath_{resourceDirectoryPath},
  resourceType_{resourceType}
{
  ///overload Ctor
}

vector<resourcesManagerClass> resourcesManagerClass::ResoucesDirectoryPath()
{
  vector<resourcesManagerClass> holdResoucesDirectoryPath;
  vector<string> ResoucesDirectoryPath{
            "resources/Font.ttf",
                                "resources/shoot.wav",
                                "resources/LevelUp_sound.wav",
                                "resources/mushroom_regenerate_sound.wav",
                                "resources/scorpion_move_sound.wav",
                                "resources/spider_move_sound.wav",
                                "resources/Centipede_resources_flea.wav",
								"resources/Player.png",
								"resources/bullet.png",
								"resources/Centipede.png",
								"resources/Mushroom.png",
								"resources/Scorpion.png",
								"resources/spider_and_score.png",
								"resources/flea.png"
        };
for(auto index_iter=0u; index_iter != ResoucesDirectoryPath.size(); index_iter++ )
{
   resourcesManagerClass resourceInfo{static_cast<defineTypeOfResource>(index_iter), ResoucesDirectoryPath.at(index_iter)};
   holdResoucesDirectoryPath.push_back(resourceInfo);
}
  return holdResoucesDirectoryPath;
}

resourcesManagerClass::defineTypeOfResource resourcesManagerClass::getresourceType() const
{
  return resourceType_;
}

string resourcesManagerClass::getresourceDirectoryPath() const
{
  return resourceDirectoryPath_;
}

void resourcesManagerClass::setResourceInfo()
{
   for(auto index = static_cast<int>(defineTypeOfResource::PLAYER); index<static_cast<int>(defineTypeOfResource::PLAYER)+2; index++)
   {
     storeResourceInfo(static_cast<defineTypeOfResource>(index), objectsDirection::NONE, 1, 1 );
   }
   auto row=2; auto col=8; auto Direction = objectsDirection::LEFT;
   for (auto index = static_cast<int>(defineTypeOfResource::CENTIPEDE); index<static_cast<int>(defineTypeOfResource::CENTIPEDE)+2; index++)
   {
     storeResourceInfo(static_cast<defineTypeOfResource>(index), Direction, row, col );
     Direction = objectsDirection::NONE;  col /=2.0f;
   }
   Direction = objectsDirection::LEFT; row--, col=4;
   for (auto index = static_cast<int>(defineTypeOfResource::SCORPION); index<static_cast<int>(defineTypeOfResource::SCORPION)+2; index++)
   {
     storeResourceInfo(static_cast<defineTypeOfResource>(index), Direction, row, col );
     Direction = objectsDirection::NONE;  col *=2.0f; row++;
   }
   Direction = objectsDirection::DOWN; row=2; col=2;
   for (auto index = static_cast<int>(defineTypeOfResource::FLEA); index<static_cast<int>(defineTypeOfResource::FLEA)+1; index++)
   {
     storeResourceInfo(static_cast<defineTypeOfResource>(index), Direction, row, col );
   }
   ////
}

void resourcesManagerClass::storeResourceInfo(defineTypeOfResource resource, objectsDirection Direction, unsigned int numberOfRows, unsigned int NumberOFColumns)
{
  // auto row_col_Vector = vector<unsigned int>{numberOfRows, NumberOFColumns};
   vector<unsigned int>row_col_Vector;
   row_col_Vector.push_back(numberOfRows); row_col_Vector.push_back(NumberOFColumns);
   auto holdInfo = pair<defineTypeOfResource, tuple<vector<unsigned int>,objectsDirection >>(resource, std::make_tuple(row_col_Vector, Direction));
   TextureInfo.insert(holdInfo);
}

tuple<vector<unsigned int>, objectsDirection> resourcesManagerClass::getResourceInfo() const
{
    auto resourceInfo = std::make_tuple(vector<unsigned int>(), objectsDirection::NONE);
    auto iterator = TextureInfo.find(resourceType_);
    if(iterator!=TextureInfo.end())  resourceInfo = iterator->second;
    return {resourceInfo};
}
