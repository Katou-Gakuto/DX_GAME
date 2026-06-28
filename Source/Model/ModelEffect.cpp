#include <string>

#include "Master.h"

#include "ModelBase.h"
#include "ModelEffect.h"
#include "ModelBase.h"
#include "ResourceEffect.h"
#include "ResourceManager.h"
#include "UtilCalc.h"

ModelEffect::ModelEffect()
: ModelBase()
, mnEffectHandle(-1)
, mvDrawPosition(UtilCalc::VZero)
, mvDrawAngle(UtilCalc::VZero)
, mvDrawSize(UtilCalc::VOne)
, mvPrePos(UtilCalc::VZero)
{    
}

ModelEffect::~ModelEffect()
{
}

// 継承モデル終了
void ModelEffect::ModelFinalize()
{
}

// ゲーム中初期化
void ModelEffect::ModelGameInit()
{
    mvDrawSize = VGet(mvDrawSize.x * mvSize.x, mvDrawSize.y * mvSize.y, mvDrawSize.z * mvSize.z);

    mvDrawAngle = VGet(mvDrawAngle.x, mvDrawAngle.y - UtilCalc::Pi, mvDrawAngle.z); 

    mvDrawPosition = VAdd(mvDrawPosition, UtilCalc::VSphericalMovePos(mvPosition.x * mvDrawSize.x, VGet(mvDrawAngle.x, -mvDrawAngle.y - (UtilCalc::Pi * 0.5f), mvDrawAngle.z)));
    mvDrawPosition = VAdd(mvDrawPosition, UtilCalc::VSphericalMovePos(mvPosition.z * mvDrawSize.z, VGet(mvDrawAngle.x, -mvDrawAngle.y, mvDrawAngle.z)));
    mvDrawPosition.y += mvPosition.y * mvDrawSize.y;
}

// ポジション更新
void ModelEffect::ModelUpdate()
{
    if (mnEffectHandle != -1)
    {
        mvDrawPosition = VAdd(mvDrawPosition, VSub(mvPosition, mvPrePos));
        mvPrePos = mvPosition;
        
       Master::mpResourceManager->GetEffectResource()->DrawEffect(mnEffectHandle, mvDrawPosition, mvDrawAngle, mvDrawSize);
    }
}

// 描画
void ModelEffect::ModelDraw()
{
}