#include "mushroomManager.h"

mushroomManager::mushroomManager(const ScreenParameters& Screen_Parameters)
:maxMushroom{30}, ScreenParameters_{Screen_Parameters}
{
    //ctor
    float Cellsize = 16.0f;
    maxColumn = static_cast<int>(floor((ScreenParameters_.getheight()-ScreenParameters_.getheight()*0.2)/Cellsize));
    maxRow = static_cast<int>(floor(ScreenParameters_.getwidth()/Cellsize));
    RowAndColumn();
}

mushroomManager::~mushroomManager()
{
    //dtor
}

std::shared_ptr<mushroomsClass> mushroomManager::makeMushroom(positionHandler position)
{
    auto mushroomPosition = screenCoordinate(position);
    auto mushroom_ptr = std::make_shared<mushroomsClass>(LinkingCoordinates(mushroomPosition));
    return mushroom_ptr;
}

bool mushroomManager::checkIfMushroomCanBeSpawn(positionHandler Position)
{
   auto mushroomPosition = screenCoordinate(Position);
    auto x=mushroomPosition.getX_position(), y=mushroomPosition.getY_position();
    if(!checkIfCoordinateCellIsFilled(x,y)) return true;
    return false;
}

std::vector<std::shared_ptr<mushroomsClass>> mushroomManager::makeMushrooms()
{
  auto numberOfMushrooms = rand()%maxMushroom + 50;
  std::vector<std::shared_ptr<mushroomsClass>> mushrooms;
  for(auto mushroom=0u; mushroom<numberOfMushrooms; mushroom++)
  {
    auto x=rand()%maxRow, y=rand()%maxColumn;
    if(!checkIfCoordinateCellIsFilled(x,y))
    {
     auto mushroomPointer = std::make_shared<mushroomsClass>(LinkingCoordinates(positionHandler(x,y)));
     mushrooms.push_back(mushroomPointer);
    }
  }
  return mushrooms;
}

positionHandler mushroomManager::screenCoordinate(positionHandler position)
{
    if (position.getX_position()>= 624.0) position.setYposition(616.0);
    auto x = round((position.getX_position()-8.0)/16.0);
    auto y = round((position.getY_position()-24.0)/16.0);
    return positionHandler(x,y);
}

positionHandler mushroomManager::LinkingCoordinates(positionHandler position)
{
  auto x=round(position.getX_position()*16+8.0),  y=round(position.getY_position()*16+24.0);
  return positionHandler(x,y);
}

bool mushroomManager::checkIfCoordinateCellIsFilled(int x, int y)
{
   auto cellID = (maxRow*(x+1) + (y+1));
   auto cell_iterator = cellIDList.find(cellID);
   if(cell_iterator != cellIDList.end())
   {
       if(cell_iterator->second) {return cell_iterator->second;}
       else cell_iterator->second = true;
   }
   return false;
}

void mushroomManager::RowAndColumn()
{
     for(auto row=0u; row<maxRow; row++)
     {
         for(auto col=0u; col<maxColumn; col++)
         {
             auto cell = (maxRow*(row+1) + (col+1));
             auto cellID = std::pair<unsigned int, bool>(cell, false);
             cellIDList.insert(cellID);
         }
     }
}
