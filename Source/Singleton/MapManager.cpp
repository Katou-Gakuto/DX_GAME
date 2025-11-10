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
: mfTileHalfSize(250.0f)
{
    mstMapData.clear();
}
MapManager::~MapManager()
{
}


// マップ情報設定
void MapManager::SetMapData(MapType mapType)
{
    mstMapData.clear();
    //mstMapData = Master::mpDataManager->GetMapData(mapType);
    switch (mapType)
    {
    case MapType::None:
        break;

    case MapType::Normal:
        mstMapData = {
            { TileData(true), TileData(), TileData() },
            { TileData(true), TileData(true), TileData() },
            { TileData(), TileData(), TileData(true) }
        };
        break;

    case MapType::Battle:
        mstMapData = {
            { TileData(true), TileData(), TileData() },
            { TileData(true), TileData(true), TileData() },
            { TileData(), TileData(), TileData(true) }
        };
        break;
    }
}

// マップ情報設定
void MapManager::SetMapData(std::vector<std::vector<TileData>> mapData)
{
    mstMapData = mapData;
    /*
    * マップタイルに応じた処理
    */
}

// 描画
void MapManager::Draw()
{
    for (int z = 0; z < mstMapData.size(); z++)
    {
        for (int x = 0; x < mstMapData[z].size(); x++)
        {
            TileData& tile = mstMapData[z][x];

            switch (tile.tileType)
            {
            case TileType::Ground:
                // 左奥
                DrawTriangle3D(VGet(tile.tileDisplacedPos.x + (x * (mfTileHalfSize + mfTileHalfSize)) + mfTileHalfSize, tile.tileDisplacedPos.y, tile.tileDisplacedPos.z + (z * (mfTileHalfSize + mfTileHalfSize)) + mfTileHalfSize),
                    VGet(tile.tileDisplacedPos.x + (x * (mfTileHalfSize + mfTileHalfSize)) - mfTileHalfSize, tile.tileDisplacedPos.y, tile.tileDisplacedPos.z + (z * (mfTileHalfSize + mfTileHalfSize)) + mfTileHalfSize),
                    VGet(tile.tileDisplacedPos.x + (x * (mfTileHalfSize + mfTileHalfSize)) + mfTileHalfSize, tile.tileDisplacedPos.y, tile.tileDisplacedPos.z + (z * (mfTileHalfSize + mfTileHalfSize)) - mfTileHalfSize),
                    GetColor(0, 0, 255),
                    TRUE);

                // 右手前
                DrawTriangle3D(VGet(tile.tileDisplacedPos.x + (x * (mfTileHalfSize + mfTileHalfSize)) + mfTileHalfSize, tile.tileDisplacedPos.y, tile.tileDisplacedPos.z + (z * (mfTileHalfSize + mfTileHalfSize)) - mfTileHalfSize),
                    VGet(tile.tileDisplacedPos.x + (x * (mfTileHalfSize + mfTileHalfSize)) - mfTileHalfSize, tile.tileDisplacedPos.y, tile.tileDisplacedPos.z + (z * (mfTileHalfSize + mfTileHalfSize)) + mfTileHalfSize),
                    VGet(tile.tileDisplacedPos.x + (x * (mfTileHalfSize + mfTileHalfSize)) - mfTileHalfSize, tile.tileDisplacedPos.y, tile.tileDisplacedPos.z + (z * (mfTileHalfSize + mfTileHalfSize)) - mfTileHalfSize),
                    GetColor(0, 0, 255),
                    TRUE);
                break;
            }
        }
    }
}