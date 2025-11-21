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
    HANDLE = 0, // ハンドル
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
    std::map<int, TileModelData> mmTileModelDatas;

	std::vector<std::vector<TileData>>* mstMapData;

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

    /*マップデータ設定*/
    inline void SetMapData(std::vector<std::vector<TileData>>* mapData){mstMapData = mapData;}
};