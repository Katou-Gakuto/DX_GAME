#pragma once
#include <map>

#include "ModelMV1.h"
#include "ModelPolygonIndexed.h"

// INPROGRESS: 作業中

// TODO: モデル作成中
// タイルモデル情報
struct TileModelData
{

};

class ModelMap : public ModelBase
{
private:
    // タイルモデルデータ
    std::map<int, TileModelData> mmTileModelDatas;

public:
};