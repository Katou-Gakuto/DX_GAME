#include "DxLib.h"

#include "Master.h"

#include "ModelBase.h"
#include "ModelMV1.h"
#include "ModelsControllerBase.h"
#include "ResourceManager.h"
#include "UtilCalc.h"

// HACK: エフェクトテスト
static int test_Effect = -1;
static int test_Effect_Handle = -1;
static int test_Effect_Time = 0;
static bool test_Effect_Bool = true;

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
    // INPROGRESS: エフェクトテスト中 初期化ちゃんとできてるか確認
    test_Effect_Time = FileRead_size((ResourceManager::msResourceFile + "Effect/Test.efk").c_str());
    test_Effect = Master::mpResourceManager->GetEffectResource(ResourceManager::msResourceFile + "Effect/Test.efk", 100.0f);
    test_Effect_Handle = Master::mpResourceManager->GetEffectHandle(test_Effect, test_Effect_Handle);
    test_Effect_Time = 0;
}

// モデル終了
void ModelMV1::ModelFinalize()
{
    if (mnModelHandle != -1)
    {
        Master::mpResourceManager->ReduceModelHandle(mnModelHandle);
    }
}
#include "KeyState.h"
#include "EffekseerForDXLib.h"
// ポジション更新
void ModelMV1::PositionUpdate()
{
    // HACK: エフェクトテスト
    if (test_Effect_Time > 60)
    {
        test_Effect_Handle = Master::mpResourceManager->GetEffectHandle(test_Effect, test_Effect_Handle);
        test_Effect_Time = 0;
        int test = GetSpeedPlayingEffekseer3DEffect(test_Effect_Handle);
        SetSpeedPlayingEffekseer3DEffect(test_Effect_Handle, 0.0f);
    }
    test_Effect_Time += 17;

    if (Master::mpKeyState->GetWordKeyDown_Board(KEY_BOARD_WORD::X))
    {
        if (test_Effect_Bool)
        {
            int test = GetSpeedPlayingEffekseer3DEffect(test_Effect_Handle);
            SetSpeedPlayingEffekseer3DEffect(test_Effect_Handle, 0.0f);
        }
        else
        {
            SetSpeedPlayingEffekseer3DEffect(test_Effect_Handle, 1.0f);
        }
        test_Effect_Bool = !test_Effect_Bool;
    }


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
    // HACK: エフェクトテスト
    Master::mpResourceManager->DrawEffect(test_Effect, VGet(0.0f, 0.0f, 0.0f));

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