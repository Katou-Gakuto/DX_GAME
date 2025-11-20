#pragma once
#include <vector>

#include "BitFlag.h"

#include "DxLib.h"

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
private:
	// サイズ
	VECTOR mvSize;

public:
	ModelBase();
	~ModelBase();

	/*初期化*/
	void Initilize();
	/*終了*/
	void Finalize();

	/*--------*/
	/*【取得】*/
	/*--------*/

	/*サイズ取得*/
	inline VECTOR GetSize() const { return mvSize; }

	/*--------*/
	/*【設定】*/
	/*--------*/

	/*サイズ設定*/
	inline void SetSize(VECTOR size) { mvSize = size; }

	/*----------------*/
	/*【継承モデル用】*/
	/*----------------*/
public:
	/*モデル描画*/
	virtual void ModelDraw() = 0;
	/*モデル描画*/
	void ModelDraw_Indexed(const std::vector<IndexedData>& modelVertexData);
	/*モデル描画*/
	void ModelDraw_Handle(const int handle);

protected:
	/*継承モデル初期化*/
	virtual void ModelInitilize() = 0;
	/*継承モデル終了*/
	virtual void ModelFinalize() = 0;
};