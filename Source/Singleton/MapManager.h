#pragma once
#include <vector>

#include "MiniMapData.h"
#include "ResourceData.h"
#include "MapData.h"
#include "Vector2.h"

#include "DxLib.h"

struct CollisionData;
struct CharacterTargetData;
class ModelMap;

class MapManager
{
private:
	// マップ情報
	/*std::vector<*/std::vector<std::vector<TileData>>/*>*/ mstMapData;

	// 生成情報

	// タイルのサイズ
	VECTOR mvTileHalfSize;

	// マップ最小ポジション
	VECTOR mvMapMinPos;

	// マップモデル
	ModelMap *mpModelMap;

	// マップ背景ハンドル
	int mnMapBackHandle;

	// マップの背景素材ハンドル
	int mnMapBackResourceHandle;

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
	inline /*std::vector<*/std::vector<std::vector<TileData>>/*>*/ GetMapData() const { return mstMapData; }

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
	enum MINI_MAP_DRAW_GRAPH_TYPE
	{
		BACK_GROUND = 0,	// 背景
		FRAME,				// 枠
		//FRAME_RADAR,		// 枠レーダー
		MINI_MAP_OUTSIDE_CHARACTER,	// ミニマップ外キャラクター
		MINI_MAP_WITHIN_CHARACTER,	// ミニマップ内キャラクター
		PLAYER,						// プレイヤー
		MAX
	};

	// HACK: 戻す
	/*const*/ Vector2 MINI_MAP_LEFT_UP_POS = Vector2(0.8f, 0.1f);

	// ディスプレイサイズ
	DisplaySize* mstDisplaySize;

	// 前のディスプレイサイズ
	DisplaySize mstPreDisplaySize;

	// ミニマップ描画サイズ
	DisplaySize mstMiniMapSize;

	// ミニマップ中央ポジション
	DisplaySize mstMiniMapCenterPos;

	// ミニマップ描画距離(x:距離 y:ミニマップ割合)
	Vector2 mstMiniMapDrawDistance;
	// ミニマップ最大描画距離
	static constexpr float MINI_MAP_DRAW_MAX_DISTANCE = 100000.0f;
	// ミニマップ最小描画距離
	static constexpr float MINI_MAP_DRAW_MIN_DISTANCE = 1000.0f;
	// キャラクター最大サイズ倍率
	static constexpr float MINI_MAP_CHARACTER_MAX_SIZE_MAGNIFICATION = 0.4f;
		// キャラクター減少サイズ倍率
	static constexpr float MINI_MAP_CHARACTER_DECREASE_SIZE_MAGNIFICATION = 0.7f;

    // ミニマップ表示用スクリーンハンドル
    int mnDrawMiniMapScreenHandle;

	// ミニマップ枠外サイズ(半分)
	Vector2_Int mstMiniMapOutsideFrameSizeHalf;
	
	// ミニマップ描画　画像　情報
	DRAW_GRAPH_DATA mstMiniMapDrawGraphData[MINI_MAP_DRAW_GRAPH_TYPE::MAX];

	struct MASK_DATA
	{
		std::vector<std::vector<int>> maskGraphPixelData;
		Vector2_Int maskSize;
		unsigned char *maskData;
	};

	// マスクデータ
	MASK_DATA mstMaskData;

public:
	/// <summary>ミニマップサイス変更(0.0f～1.0f)</summary>
	void SetMiniMapSize_And_CreateHandle(Vector2 minMapSize);

	/// <summary>ミニマップ描画長さ変更</summary>
	/// <returns>成功フラグ</returns>
	bool SetMiniMapDrawLength(float minMapDrawLength);

	/// <summary>ミニマップ描画</summary>
	void DrawMiniMap();

private:
	/*必要ならミニマップスクリーンハンドル作成する*/
	void CreateMiniMapScreenHandle(bool createRequiredFlag = false);

	/*ミニマップ表示ポジション取得*/
	ALL_MINI_MAP_DRAW_DATA GetMiniMapDrawPos();

	/*マスクリセット*/
	void ReSetMask(int width, int height);
};