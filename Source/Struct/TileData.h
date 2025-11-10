#pragma once
#include <vector>

#include "BitFlag.h"

#include "DxLib.h"

enum class MapType
{
	None = 0,			// 何もない
	Normal = 1,			// 通常マップ
	Battle = 2,			// 戦闘マップ
};

enum class TileType
{
	None = 0,			// 何もない
	Ground = 1,			// 地面
};

// タイルのポジション
struct TilePos
{
public:
	int x;
	int y;
};

// タイルデータ
struct TileData
{
public:
	TileData();
	TileData(bool flag);

	std::vector<TilePos> adjacentData; // 隣接タイル情報

	BIT_FLAG<unsigned long long> tileFlag;	// このタイルのフラグデータ

	TileType tileType;	// タイルの種類

	VECTOR tileDisplacedPos;	// このタイルのずれたベクトル
};