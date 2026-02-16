#pragma once
#include <vector>

#include "BitFlag.h"

#include "DxLib.h"

class CharacterBase;
class MapManager;

// TODO: マップ名に変える　(ファイルから最終的に取得する)
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
	int z;
	
	BIT_FLAG<unsigned long long>* tileFlag;

	TilePos() = default;
	TilePos(int X, int Z)
	{
		x = X;
		z = Z;

		tileFlag = nullptr;
	}

	bool operator ==(TilePos src)
	{
		return ((src.x == this->x) && (src.z == this->z));
	}
	bool operator !=(TilePos src)
	{
		return ((src.x != this->x) || (src.z != this->z));
	}
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

	TilePos tilePos;	// タイルポジション

	/*タイル処理*/
	virtual TilePos TileProcess(CharacterBase* character, MapManager* mapManager);
};