#include <string>

#include "Master.h"

#include "ModelBase.h"
#include "ModelEffect.h"
#include "ModelsControllerBase.h"
#include "ResourceEffect.h"
#include "ResourceManager.h"
#include "UtilCalc.h"

ModelEffect::ModelEffect()
: mnEffectHandle(-1)
{
    
}

ModelEffect::~ModelEffect()
{
}

// 継承モデル初期化
void ModelEffect::ModelInitilize()
{
}

// 継承モデル終了
void ModelEffect::ModelFinalize()
{
}

// ゲーム中初期化
void ModelEffect::GameInit()
{
    mvDrawSize = mpModelsController->GetModelSize();
    mvDrawSize = VGet(mvDrawSize.x * mvSize.x, mvDrawSize.y * mvSize.y, mvDrawSize.z * mvSize.z);

    mvDrawAngle = mpModelsController->GetModelAngle();
    mvDrawAngle = VGet(mvDrawAngle.x, mvDrawAngle.y - UtilCalc::Pi, mvDrawAngle.z); 

    mvDrawPosition = mpModelsController->GetModelPosition();
    mvPreModelControllerPos = mvDrawPosition;
    mvDrawPosition = VAdd(mvDrawPosition, UtilCalc::VSphericalMovePos(mvPosition.x * mvDrawSize.x, VGet(mvDrawAngle.x, -mvDrawAngle.y - (UtilCalc::Pi * 0.5f), mvDrawAngle.z)));
    mvDrawPosition = VAdd(mvDrawPosition, UtilCalc::VSphericalMovePos(mvPosition.z * mvDrawSize.z, VGet(mvDrawAngle.x, -mvDrawAngle.y, mvDrawAngle.z)));
    mvDrawPosition.y += mvPosition.y * mvDrawSize.y;
}

// ポジション更新
void ModelEffect::PositionUpdate()
{
    if (mnEffectHandle != -1)
    {
        mvDrawPosition = VAdd(mvDrawPosition, VSub(mpModelsController->GetModelPosition(), mvPreModelControllerPos));
        mvPreModelControllerPos = mpModelsController->GetModelPosition();
        
       Master::mpResourceManager->GetEffectResource()->DrawEffect(mnEffectHandle, mvDrawPosition, mvDrawAngle, mvDrawSize);
    }
}

// 描画
void ModelEffect::ModelDraw()
{
}