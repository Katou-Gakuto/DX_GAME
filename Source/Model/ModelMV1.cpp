#include "DxLib.h"

#include "Master.h"

#include "DrawManager.h"
#include "ModelBase.h"
#include "ModelMV1.h"
#include "ResourceManager.h"
#include "Resource3DModel.h"
#include "UtilCalc.h"

ModelMV1::ModelMV1()
: ModelBase()
, mnModelHandle(-1)
{
}
ModelMV1::~ModelMV1()
{
}

// モデル終了
void ModelMV1::ModelFinalize()
{
    if (mnModelHandle != -1)
    {
        Master::mpResourceManager->Get3DModelResource()->ReduceResourceHandle(mnModelHandle);
    }
}

// ポジション更新
void ModelMV1::ModelUpdate()
{
    VECTOR size     = mvSize;
    VECTOR angle    = mvAngle;
    VECTOR position = mvPosition;

    // // モデルコントローラーを反映する
    // if (mpModelsController != nullptr)
    // {
    //     size     = UtilCalc::VMultiply(size,     mpModelsController->GetModelSize());
    //     angle    = VAdd(angle,    mpModelsController->GetModelAngle());
    //     position = VAdd(position, mpModelsController->GetModelPosition());

        // 回転の中心を上にする
        {
            // HACK: 回転後回し
            // X回転
            VECTOR anglePos = UtilCalc::VSphericalMovePos(mvSize.y * 80.0f, VGet(angle.x + (UtilCalc::Pi * 1.5f), -angle.y, angle.z));
            position = VAdd(position, VGet(anglePos.x, anglePos.y, anglePos.z));
            
            //VECTOR anglePos = UtilCalc::VSphericalMovePos(mpModelsController->GetModelSize().y * TEST_FLOAT[0], VGet((angle.x * TEST_FLOAT[1] * TEST_FLOAT[3]) + (UtilCalc::Pi * TEST_FLOAT[2]), -angle.y, angle.z));
            //position = VAdd(position, VGet(-anglePos.x, anglePos.y, -anglePos.z));

          /*  
                    // 回転させる
        float totalRotational = (mfMaxAttackMiddleMotionTime - (GetAnimCount() / mfMaxAttackMiddleMotionTime));

        MV1SetRotationXYZ(mnModelHandle, VGet(totalRotational * (DX_PI_F * 2.0f), mfAngle + DX_PI_F, 0.0f));

        VECTOR tempPosition2 = Calculation::GetSphericalMove(mpCharacter->GetStatus().size, (totalRotational * (DX_PI_F * 2.0f)) + (DX_PI_F * 1.5), -mfAngle);
        //tempPosition2.x = ATTACK_MIDDLE_XYZ_SET * cosf(Calculation::GetNotExceedAngle((totalRotational * (DX_PI_F * 2.0f)) + (DX_PI_F * 1.5))) * sinf(Calculation::GetNotExceedAngle(-mfAngle));
        //tempPosition2.y = ATTACK_MIDDLE_XYZ_SET * sinf(Calculation::GetNotExceedAngle((totalRotational * (DX_PI_F * 2.0f)) + (DX_PI_F * 1.5)));
        //tempPosition2.z = -(ATTACK_MIDDLE_XYZ_SET * cosf(Calculation::GetNotExceedAngle((totalRotational * (DX_PI_F * 2.0f)) + (DX_PI_F * 1.5))) * cosf(Calculation::GetNotExceedAngle(-mfAngle)));

        SetPosition(VAdd(VAdd(mpCharacter->GetObjectPosition(), 
                            VGet(0.0f, mpCharacter->GetStatus().size, 0.0f)),
                    VGet(-tempPosition2.x, tempPosition2.y, -tempPosition2.z)));
            */

        //VECTOR tempPosition2 = Calculation::GetSphericalMove(mpCharacter->GetStatus().size, (totalRotational * (DX_PI_F * 2.0f)) + (DX_PI_F * 1.5), -mfAngle);
        //tempPosition2.x = ATTACK_MIDDLE_XYZ_SET * cosf(Calculation::GetNotExceedAngle((totalRotational * (DX_PI_F * 2.0f)) + (DX_PI_F * 1.5))) * sinf(Calculation::GetNotExceedAngle(-mfAngle));
        //tempPosition2.y = ATTACK_MIDDLE_XYZ_SET * sinf(Calculation::GetNotExceedAngle((totalRotational * (DX_PI_F * 2.0f)) + (DX_PI_F * 1.5)));
        //tempPosition2.z = -(ATTACK_MIDDLE_XYZ_SET * cosf(Calculation::GetNotExceedAngle((totalRotational * (DX_PI_F * 2.0f)) + (DX_PI_F * 1.5))) * cosf(Calculation::GetNotExceedAngle(-mfAngle)));


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
        position.y += mvSize.y * 80.0f;
    //}

    // 位置・角度・サイズ設定
    MV1SetScale(       mnModelHandle, size);
    MV1SetRotationXYZ( mnModelHandle, angle);
    MV1SetPosition(    mnModelHandle, position);
}

// モデル描画
void ModelMV1::ModelDraw()
{
    if (!mbDrawFlag)
    {
        return;
    }
    
    Master::mpDrawManager->DrawModelHandle(mnModelHandle);
}

// モデルハンドル設定
void ModelMV1::SetModelHandle(const char* filePath)
{
    if (mnModelHandle != -1)
    {
        Master::mpResourceManager->Get3DModelResource()->ReduceResourceHandle(mnModelHandle);
    }

    mnModelHandle = Master::mpResourceManager->Get3DModelResource()->GetResourceHandle(filePath);
}