#include <vector>

#include "BitFlag.h"
#include "TileData.h"

#include "DxLib.h"

#include "UtilCalc.h"

// タイルデータ
TileData::TileData()
: tileType(TileType::None)
, tileDisplacedPos(UtilCalc::VZero())
, tileFlag(BIT_FLAG<unsigned long long>(0))
{
	adjacentData.clear();
}
// タイルデータ
TileData::TileData(bool flag)
: tileType(TileType::Ground)
, tileDisplacedPos(UtilCalc::VZero())
, tileFlag(BIT_FLAG<unsigned long long>(0))
{
	adjacentData.clear();
}