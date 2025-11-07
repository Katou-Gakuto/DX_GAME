#include <fstream>
#include <string>
#include <vector>

#include "BitFlag.h"
#include "TileData.h"

#include "DxLib.h"

#include "Master.h"

#include "DataManager.h"
#include "MapManager.h"

MapManager::MapManager()
{
}
MapManager::~MapManager()
{
}


// ƒ}ƒbƒvî•ñÝ’è
void MapManager::SetMapData(MapType mapType)
{
    //mstMapData = Master::mpDataManager->GetMapData(mapType);
    mstMapData = {
        { TileData(), TileData(), TileData() },
        { TileData(), TileData(), TileData() },
        { TileData(), TileData(), TileData() } 
    }; 
}