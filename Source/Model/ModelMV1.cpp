#include "DxLib.h"

#include "Master.h"

#include "ModelBase.h"
#include "ModelMV1.h"
#include "ResourceManager.h"

ModelMV1::ModelMV1()
: mModelHandle(-1)
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
    if (mModelHandle != -1)
    {
        Master::mpResourceManager->ReduceModelHandle(mModelHandle);
    }
}

// モデル描画
void ModelMV1::ModelDraw()
{
    if (mModelHandle != -1)
    {
        MV1DrawModel(mModelHandle);
    }
}

// モデルハンドル設定
void ModelMV1::SetModelHandle(const char* filePath)
{
    if (mModelHandle != -1)
    {
        Master::mpResourceManager->ReduceModelHandle(mModelHandle);
    }

    mModelHandle = Master::mpResourceManager->GetModelHandle(filePath);
}