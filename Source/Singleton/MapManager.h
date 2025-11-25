#pragma once
#include <vector>

#include "TileData.h"

#include "DxLib.h"

struct CollisionData;
struct CharacterTargetData;
class ModelMap;

// TODO: マップ右前に伸びてるのを右後ろに直す　現状Z+方向がX+方向になってX+方向がZ-方向に伸びている
class MapManager
{
private:
	// マップ情報
	std::vector<std::vector<TileData>> mstMapData;

	// タイルのサイズ
	float mfTileHalfSize;

	// マップ最小ポジション
	VECTOR mvMapMinPos;

	// マップモデル
	ModelMap *mpModelMap;

public:
	MapManager();
	~MapManager();

	/*マップ情報設定*/
	void SetMapData(MapType maptype);
	/*マップ情報設定*/
	void SetMapData(std::vector<std::vector<TileData>> mapData);

	/*マップ情報取得*/
	inline std::vector<std::vector<TileData>> GetMapData() const { return mstMapData; }

	/*マップ当たり判定*/
	void MapCollision();

	/*キャラクターとの当たり判定*/
	std::vector<CharacterTargetData> CharacterCollision(std::vector<CharacterTargetData> characterData);

	/*マップポジション取得*/
	void GetMapPos(int &setPosX, int &setPosZ, VECTOR pos);

	/*描画*/
	void Draw();

	/*タイルサイズ取得*/
	inline float GetTileSize() const { return mfTileHalfSize + mfTileHalfSize; }
};