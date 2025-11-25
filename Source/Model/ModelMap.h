#pragma once
#include <map>
#include <vector>

#include "TileData.h"

#include "ModelMV1.h"

// INPROGRESS: 作業中

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

public:
    ModelMap();
    ~ModelMap();

protected:
    /*モデル初期化*/
    void ModelInitilize() override;
    /*モデル終了*/
    void ModelFinalize() override;

public:
    /*モデル描画*/
    void ModelDraw() override;

    /*マップデータ読み込み*/
    void LoadMapData(std::vector<std::vector<TileData>>& mapData);

    /*マップモデル解放*/
    void ReleaseMapModel();
};