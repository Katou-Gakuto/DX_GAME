#pragma once
#include <vector>

#include "BitFlag.h"

#include "DxLib.h"

#include "ModelBase.h"

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

/*---------------------------------*/
/*【ポリゴンインデックスモデルクラス】*/
/*---------------------------------*/
class ModelPolygonIndexed : public ModelBase
{
private:
    std::vector<IndexedData> mstModelVertex; // モデルデータ
public:
    ModelPolygonIndexed();
    ~ModelPolygonIndexed();

protected:
	/*継承モデル初期化*/
	virtual void ModelInitilize() override;
	/*継承モデル終了*/
	virtual void ModelFinalize() override;

public:
	/*モデル描画*/
	virtual void ModelDraw() override;
    
    /*モデルデータ追加*/
    inline void AddModelData(const IndexedData& data) { mstModelVertex.push_back(data); }
};