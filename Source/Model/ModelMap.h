#pragma once
#include <map>
#include <vector>

#include "MapData.h"

#include "ModelMV1.h"

/*-------------------*/
/*【タイルモデル情報】*/
/*-------------------*/
// タイルモデル種類
enum class TILE_MODEL_TYPE
{
    NONE = 0,   // 無い
    HANDLE,     // ハンドル
    INDEXED,    // 頂点
};

// TODO: モデル作成中
// タイルモデル情報
struct TileModelData
{
    TILE_MODEL_TYPE tileModelType; // タイルモデル種類

    int modelHandle; // モデルハンドル

    std::vector<IndexedData> modelVertex; // モデル頂点情報
};

class ModelMap : public ModelBase
{
private:
    // タイルモデルデータ
    std::vector<std::vector<TileModelData>> mstTileModelDatas;

    // 地面モデル画像ハンドル
    int mnGroundModelGraphHandle;

public:
    ModelMap();
    ~ModelMap();
    
    /// <summary>初期化</summary>
    void Initilize();

protected:
    /*継承モデル ゲーム初期化*/
    void ModelGameInit() override;
    /*モデル終了*/
    void ModelFinalize() override;
    
	/*継承モデル 更新*/
	void ModelUpdate() override;

public:
    /*モデル描画*/
    void ModelDraw() override;

    /*マップデータ読み込み*/
    void LoadMapData(std::vector<std::vector<TileData>>& mapData, VECTOR mapMinPos, VECTOR tileHalfSize);

    /*マップモデル解放*/
    void ReleaseMapModel();
};