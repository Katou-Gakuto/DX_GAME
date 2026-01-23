#include "DxLib.h"

#include "Master.h"

#include "ModelBase.h"
#include "ModelMV1.h"
#include "ModelsControllerBase.h"
#include "ResourceManager.h"
#include "UtilCalc.h"

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

// ポジション更新
void ModelMV1::PositionUpdate()
{
    VECTOR size     = mvSize;
    VECTOR angle    = mvAngle;
    VECTOR position = mvPosition;

    // モデルコントローラーを反映する
    if (mpModelsController != nullptr)
    {
        size     = UtilCalc::VMultiply(size,     mpModelsController->GetModelSize());
        angle    = VAdd(angle,    mpModelsController->GetModelAngle());// TODO: 行列で計算予定
        position = VAdd(position, mpModelsController->GetModelPosition());

        // 回転の中心を上にする
        {
            // X回転
            VECTOR anglePos = UtilCalc::VSphericalMovePos(100.0f, VGet(angle.x + (UtilCalc::Pi * 1.5f), -angle.y, angle.z));
            position = VAdd(position, VGet(anglePos.x, anglePos.y, anglePos.z));

            // TODO: 計算完成させる
            // Z回転
            // anglePos = UtilCalc::VSphericalMovePos(100.0f, VGet(angle.z + (UtilCalc::Pi * 1.5f), -angle.y, angle.x));
            // if (UtilCalc::Abs(angle.y) > (UtilCalc::Pi * 0.3f))
            // {
            //     position = VAdd(position, VGet(anglePos.z, anglePos.y, 0.0f));
            // }
            // else
            // {
            //     position = VAdd(position, VGet(anglePos.x /*((UtilCalc::Abs(angle.y) - (UtilCalc::Pi * 0.5f))  * 0.6369426f)*/, anglePos.y, 0.0f));
            // }
        }

        // 高さの修正
        position.y += mpModelsController->GetModelSize().y * 100.0f;
    }

    // 位置・角度・サイズ設定
    MV1SetScale(       mnModelHandle, size);
    MV1SetRotationXYZ( mnModelHandle, angle);
    MV1SetPosition(    mnModelHandle, position);
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