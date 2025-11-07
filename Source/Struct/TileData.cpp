#include <vector>

#include "BitFlag.h"
#include "TileData.h"

#include "DxLib.h"

#include "UtilCalc.h"

// タイルデータ
TileData::TileData()
: tileType(TileType::None)
, tilePos(UtilCalc::VZero())
, tileFlag(BIT_FLAG<unsigned long long>(0))
{
	adjacentData.clear();
}