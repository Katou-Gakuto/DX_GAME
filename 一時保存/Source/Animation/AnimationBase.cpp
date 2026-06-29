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

// シーン最終初期化
void AnimationBase::SceneLastInitilize()
{
    Update();
}

// 終了
void AnimationBase::Finalize()
{
    if (mpFsm != nullptr)
    {
        mpFsm->Finalize(this);

        delete mpFsm;
    }

    mstAnimationDatas.clear();
}

// アニメーション更新テスト
void AnimationBase::Update()
{
    if (mpFsm != nullptr)
    {
        mpFsm->Update(this, mstAnimationDatas);
    }
}