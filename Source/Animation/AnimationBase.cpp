#include "AnimationBase.h"

#include "FSM.h"

AnimationBase::AnimationBase()
: mpModelsController(nullptr)
{
    mstAnimationDatas.clear();
    mpFsm = nullptr;
}

// 初期化
void AnimationBase::Initilize()
{
    // HACK: あとで削除
    // FSM生成
    mpFsm = new FSMAnimation();
}

// 終了
void AnimationBase::Finalize()
{
    mstAnimationDatas.clear();
    delete mpFsm;
}

// アニメーション更新
void AnimationBase::Update()
{
    mpFsm->Update(this, mstAnimationDatas);
}