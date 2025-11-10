#pragma once
#include <vector>

#include "BitFlag.h"
#include "TileData.h"

#include "DxLib.h"


class MapManager
{
private:
	// マップ情報
	std::vector<std::vector<TileData>> mstMapData;

	// タイルのサイズ
	float mfTileHalfSize;

public:
	MapManager();
	~MapManager();

	/*マップ情報設定*/
	void SetMapData(MapType maptype);
	/*マップ情報設定*/
	void SetMapData(std::vector<std::vector<TileData>> mapData);

	/*マップ情報取得*/
	inline std::vector<std::vector<TileData>> GetMapData() const { return mstMapData; }

	/*描画*/
	void Draw();
};