#include "DxLib.h"

#include "Master.h"

#include "ModelBase.h"
#include "ModelMV1.h"
#include "ResourceManager.h"

ModelMV1::ModelMV1()
: mnModelHandle(-1)
{
}
ModelMV1::~ModelMV1()
{
}

// モデル初期化
void ModelMV1::ModelInitilize()
{
}

// モデル終了
void ModelMV1::ModelFinalize()
{
    if (mnModelHandle != -1)
    {
        Master::mpResourceManager->ReduceModelHandle(mnModelHandle);
    }
}

// モデル描画
void ModelMV1::ModelDraw()
{
    ModelDraw_Handle(mnModelHandle);
}

// モデルハンドル設定
void ModelMV1::SetModelHandle(const char* filePath)
{
    if (mnModelHandle != -1)
    {
        Master::mpResourceManager->ReduceModelHandle(mnModelHandle);
    }

    mnModelHandle = Master::mpResourceManager->GetModelHandle(filePath);
}