#pragma once
#include <vector>

#include "MinMapData.h"
#include "ResourceData.h"
#include "TileData.h"
#include "Vector2.h"

#include "DxLib.h"

struct CollisionData;
struct CharacterTargetData;
class ModelMap;

class MapManager
{
private:
	// マップ情報
	std::vector<std::vector<TileData>> mstMapData;

	// タイルのサイズ
	VECTOR mvTileHalfSize;

	// マップ最小ポジション
	VECTOR mvMapMinPos;

	// マップモデル
	ModelMap *mpModelMap;

public:
	MapManager();
	~MapManager();

	/// <summary>初期化</summary>
	void Initilize();
	/// <summary>終了</summary>
	void Finalize();

	/// <summary>データ解放</summary>
	void Release();

	/*マップ情報設定*/
	void SetMapData(MapType mapType);
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
	inline VECTOR GetTileSize() const { return VAdd(mvTileHalfSize, mvTileHalfSize); }

	/*--------------*/
	/*【ミニマップ】*/
	/*--------------*/
private:
	// ミニマップ画像種類
	enum MIN_MAP_DRAW_GRAPH_TYPE
	{
		BACK_GROUND = 0,	// 背景
		FRAME,				// 枠
		MASK,				// マスク
		MIN_MAP_OUTSIDE_CHARACTER,	// ミニマップ外キャラクター
		MIN_MAP_WITHIN_CHARACTER,	// ミニマップ内キャラクター
		PLAYER,						// プレイヤー
		MAX
	};

	// HACK: 戻す
	/*const*/ Vector2 MIN_MAP_LEFT_UP_POS = Vector2(0.8f, 0.1f);

	// ディスプレイサイズ
	DisplaySize* mstDisplaySize;

	// 前のディスプレイサイズ
	DisplaySize mstPreDisplaySize;

	// ミニマップサイズ
	DisplaySize mstMinMapSize;

	// ミニマップ中央ポジション
	DisplaySize mstMinMapCenterPos;

	// ミニマップ描画距離(x:距離 y:ミニマップ割合)
	Vector2 mstMinMapDrawDistance;
	// ミニマップ最大描画距離
	static constexpr float MIN_MAP_DRAW_MAX_DISTANCE = 10000.0f;
	// ミニマップ最小描画距離
	static constexpr float MIN_MAP_DRAW_MIN_DISTANCE = 200.0f;

    // ミニマップ表示用スクリーンハンドル
    int mnDrawMinMapScreenHandle;
	
	// ミニマップ描画　画像　情報
	DRAW_GRAPH_DATA mstMinMapDrawGraphData[MIN_MAP_DRAW_GRAPH_TYPE::MAX];

	struct MASK_DATA
	{
		int maskHandle;
		unsigned char maskData[16][16];
	};

	// マスクデータ
	MASK_DATA mstMaskData;

public:
	/// <summary>ミニマップサイス変更(0.0f～1.0f)</summary>
	inline void SetMinMapSize_And_CreateHandle(Vector2 minMapSize) { mstMinMapSize = minMapSize; CreateMinMapScreenHandle(true); }

	/// <summary>ミニマップ描画長さ変更</summary>
	/// <returns>成功フラグ</returns>
	bool SetMinMapDrawLength(float minMapDrawLength);

	/// <summary>ミニマップ描画</summary>
	void DrawMinMap();

private:
	/*必要ならミニマップスクリーンハンドル作成する*/
	void CreateMinMapScreenHandle(bool createRequiredFlag = false);

	/*ミニマップ表示ポジション取得*/
	ALL_MIN_MAP_DRAW_DATA GetMinMapDrawPos();

	/*マスクリセット*/
	void ReSetMask(int width, int height);
};