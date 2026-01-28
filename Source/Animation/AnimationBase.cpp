#include "AnimationBase.h"

#include "FSM.h"

AnimationBase::AnimationBase()
: mpModelsController(nullptr)
{
    mmAnimationTime.clear();
    
    mstAnimationDatas.clear();
    mpFsm = nullptr;
}

// 初期化
void AnimationBase::Initilize()
{
    if (mpFsm != nullptr)
    {
        mpFsm->Initilize(this);
    }
}

// 終了
void AnimationBase::Finalize()
{
    mstAnimationDatas.clear();
    if (mpFsm != nullptr)
    {
        delete mpFsm;
    }
}

// アニメーション更新
void AnimationBase::Update()
{
    if (mpFsm != nullptr)
    {
        mpFsm->Update(this, mstAnimationDatas);
    }
}