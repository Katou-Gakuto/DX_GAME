#pragma once
#include <vector>

#include "BitFlag.h"
#include "ResourceData.h"

#include "DxLib.h"

#include "Animation.h"

/*-------------------------------*/
/*【ポリゴンインデックスモデル情報】*/
/*-------------------------------*/
// テクスチャ種類
enum class TEXTURE_TYPE
{
    GRAPH = 0, // グラフィック
    MOVIE, // ムービー
};

// インデックス情報
struct IndexData
{
    unsigned short v1; // 頂点1
    unsigned short v2; // 頂点2
    unsigned short v3; // 頂点3
};

// 頂点情報
struct IndexedData
{
    std::vector<VERTEX3D> vertex;// 頂点情報
    std::vector<IndexData> index; // インデックス情報
    int textureHandle; // テクスチャハンドル
    BIT_FLAG<unsigned char> textureType; // テクスチャ種類
    int transFlag;    // 透過フラグ
};

class ModelBase
{
protected:

	Animation* mpAnimation;

	// ポジション
	VECTOR mvPosition;
	// 角度
	VECTOR mvAngle;
	// サイズ
	VECTOR mvSize;

	// 描画フラグ
	bool mbDrawFlag;

public:
	ModelBase();
	~ModelBase();
	
    /// <summary>シーン最終初期化</summary>
    void SceneLastInitilize();
	/// <summary>終了</summary>
	void Finalize();

	/// <summary>ゲーム初期化</summary>
	virtual void ModelGameInit(VECTOR position, VECTOR angle, VECTOR size);

	/// <summary>更新</summary>
	void Update(VECTOR position, VECTOR angle);

	/// <summary>描画</summary>
	virtual void ModelDraw() = 0;
	/*--------*/
	/*【取得】*/
	/*--------*/

	/// <summary>アニメーション取得</summary>
	Animation* GetAnimation() { return mpAnimation; }
	/*ポジション取得*/
	inline VECTOR GetPosition() const { return mvPosition; }
	/*角度取得*/
	inline VECTOR GetAngle() const { return mvAngle; }
	/*サイズ取得*/
	inline VECTOR GetSize() const { return mvSize; }

	/// <summary>描画フラグ取得</summary>
	inline bool GetDrawFlag() const { return mbDrawFlag; }

	/*--------*/
	/*【設定】*/
	/*--------*/

	/// <summary>このモデルのアニメーションとして設定</summary>
	Animation* MyAnimationSetting(Animation* animtion);
	/*ポジション設定*/
	inline void SetPosition(VECTOR position) { mvPosition = position; }
	/*角度設定*/
	inline void SetAngle(VECTOR angle) { mvAngle = angle; }
	/*サイズ設定*/
	inline void SetSize(VECTOR size) { mvSize = size; }

	/// <summary>描画フラグ設定</summary>
	inline void SetDrawFlag(bool drawFlag) { mbDrawFlag = drawFlag; }

	/*----------------*/
	/*【継承モデル用】*/
	/*----------------*/

	/*--------------------------*/
	/*     【継承用モデル】     */
	/*--------------------------*/
	/*------------*/
	/*【継承処理】*/
	/*------------*/
protected:
	/*継承モデル 終了*/
	virtual void ModelFinalize() {}

	/*継承モデル ゲーム初期化*/
	virtual void ModelGameInit() = 0;
	/*継承モデル 更新*/
	virtual void ModelUpdate() = 0;

	/*--------------*/
	/*【取得・設定】*/
	/*--------------*/
public:
	/// <summary>ハンドル取得</summary>
	virtual int GetHandle() const { return -1; }
	/// <summary>ハンドル取得</summary>
	virtual int* GetHandlePointer() { return nullptr; }
	/// <summary>ハンドル取得</summary>
	virtual std::vector<DRAW_GRAPH_DATA>* GetDrawData() { return nullptr; }

	/// <summary>モデル描画情報の取得</summary>
	inline virtual DrawConfigData GetDrawConfigData() { return DrawConfigData(); }
	/// <summary>モデル描画情報の設定</summary>
	inline virtual void SetDrawConfigData(DrawConfigData drawConfigData) {}


// 	/*モデル描画*/
// 	virtual void ModelDraw() = 0;
// 	/*モデル描画(頂点)*/
// 	void ModelDraw_Indexed(const std::vector<IndexedData>& modelVertexData);
// 	/*モデル描画(モデルハンドル)*/
// 	void ModelDraw_Handle(const int handle);
// 	/*モデル描画(画像)*/
// 	void ModelDraw_Graph(const DRAW_GRAPH_DATA drawData);
// 	/*モデル描画(動画)*/
// 	void ModelDraw_Movie(const DRAW_GRAPH_DATA drawData);

};