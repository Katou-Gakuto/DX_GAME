#include <string>

#include "Master.h"

#include "ModelBase.h"
#include "ModelEffect.h"
#include "ModelsControllerBase.h"
#include "ResourceManager.h"

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
    if (mnEffectHandle != -1)
    {
        Master::mpResourceManager->ReduceEffect(mnEffectHandle);
    }
}

// ゲーム中初期化
void ModelEffect::GameInit()
{
    mvPosition = mpModelsController->GetModelPosition();
}

// ポジション更新
void ModelEffect::PositionUpdate()
{
    if (mnEffectHandle != -1)
    {
        Master::mpResourceManager->DrawEffect(mnEffectHandle, mvPosition);
    }
}

// 描画
void ModelEffect::ModelDraw()
{
}