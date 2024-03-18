#include "HashGrid.h"
#include <cmath>
HashGrid::HashGrid(const ScreenParameters Screen_Parameters_)
:cellSize{80}, ScreenParameters_{Screen_Parameters_}
{
    //ctor
    ConstructMap();
}

HashGrid::~HashGrid()
{
    //dtor
}

void HashGrid::constructSpatialGrid(std::vector<entityBaseClass_ptr>& gameobjects)
{
   remove();
   for(auto& object : gameobjects)
   {
       storePosition(object);
   }
   return;
}

std::vector<entityBaseClass_ptr> HashGrid::DetectNearObjects(entityBaseClass_ptr object)
{
    std::vector<entityBaseClass_ptr> nearObjects;
    std::vector<unsigned int> Cells(5);

    auto gameobjectsPositions = getObjectPositions(object);
    auto gameobjectsCellPositions = makeMapKeys(gameobjectsPositions);

    //
    std::sort(gameobjectsCellPositions.begin(), gameobjectsCellPositions.end());
    auto iter = std::unique_copy(gameobjectsCellPositions.begin(),gameobjectsCellPositions.end(), Cells.begin());

    //
    Cells.resize(std::distance(Cells.begin(), iter));

    //
    for(auto& cell: Cells)
    {
        auto iterator = gameObjects.find(cell);
        if(iterator != gameObjects.end())
        {
            for(auto& object_in_proximity : iterator->second)
            {
                if(object!=object_in_proximity)
                {
                    if(std::count(nearObjects.begin(), nearObjects.end(), object_in_proximity) == 0)
                        nearObjects.push_back(object_in_proximity);
                }
            }
        }
    }
  return nearObjects;
}

void HashGrid::remove()
{
    auto iterator = gameObjects.begin();
    auto last = gameObjects.end();
    for(; iterator!=last; iterator++)
    {
        (iterator->second).clear();
    }
    return;
}

void HashGrid::ConstructMap()
{
    auto  MaxCol = ScreenParameters_.getwidth()/cellSize; auto MaxRow = ScreenParameters_.getheight()/cellSize;
    auto  maxColumn = static_cast<float>(std::floor(MaxCol)),
          maxRow = static_cast<float>(std::floor(MaxRow));

         if((MaxRow)%cellSize != 0) ++maxRow;
         if((MaxCol)%cellSize != 0) ++maxColumn;

    auto HashGridID = 0;
    for(auto CellIDRow =0; CellIDRow<maxRow; CellIDRow++){
        for(auto CellIDColumn = 0; CellIDColumn<maxColumn; CellIDColumn++){
            auto holdPair = std::pair<int, std::vector<entityBaseClass_ptr>>(HashGridID, std::vector<entityBaseClass_ptr>());
            gameObjects.insert(holdPair);
            ++HashGridID;
        }
    }
}

std::vector<positionHandler> HashGrid::getObjectPositions(entityBaseClass_ptr& object)
{
      std::vector<positionHandler> objectsPosition(5);
      auto iterator = objectsPosition.begin();
      (*iterator) = object->getPosition();

    for(auto& Vertex: object->getBoundary().getVertices())
    {
      ++iterator; (*iterator) = Vertex;
    }
    return objectsPosition;
}

std::vector<unsigned int> HashGrid::makeMapKeys(std::vector<positionHandler>& positions)
{
   std::vector<unsigned int> objectCellIDPositions(5);
   auto iterator = objectCellIDPositions.begin();

   for(auto& position: positions)
   {
       (*iterator) = makeMapKey(position);
       ++iterator;
   }
   return objectCellIDPositions;
}

void HashGrid::storePosition(entityBaseClass_ptr object)
{
    auto gameobjectPositions = getObjectPositions(object);
    auto gameobjectsCEllIDPosition = makeMapKeys(gameobjectPositions);

    for(auto& cellID: gameobjectsCEllIDPosition)
    {
        auto iterator = gameObjects.find(cellID);
        if(iterator != gameObjects.end())
        {
            auto iter = std::find(begin(iterator->second), end(iterator->second), object);
            if(iter == (iterator->second).end()) (iterator->second).push_back(object);
        }
    }
    return;
}

unsigned int HashGrid::makeMapKey(const positionHandler& position)
{
  auto Xpos = static_cast<float>(std::floor(position.getX_position()/cellSize)),
       Ypos = static_cast<float>(std::floor(position.getY_position()/cellSize));
  int Id = ((Xpos*(ScreenParameters_.getheight()/cellSize)+Ypos));
  return Id;
}
