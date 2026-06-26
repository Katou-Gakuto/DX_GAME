#include "AnimationBase.h"

#include "FSMAnimation.h"

AnimationBase::AnimationBase()
    : mpModelsController(nullptr)
    , mpFsm(nullptr)
{
    mmAnimationTime.clear();
    mstAnimationDatas.clear();
}

/*----------*/
/* 初期化 */
/*----------*/
void AnimationBase::Initilize()
{
    if (mpFsm == nullptr)
    {
        return;
    }

    if (mstAnimationDatas.empty())
    {
        return;
    }

    AnimationDatas* animationDatas =
        mstAnimationDatas.front();

    if (animationDatas->animDatas.empty())
    {
        return;
    }

    auto& oneAnimationData =
        animationDatas->animDatas.begin()->second;

    mpFsm->Initilize(
        this,
        &oneAnimationData,
        animationDatas);
}

/*----------*/
/* シーン最終初期化 */
/*----------*/
void AnimationBase::SceneLastInitilize()
{
    Update();
}

/*----------*/
/* 終了 */
/*----------*/
void AnimationBase::Finalize()
{
    if (mpFsm != nullptr)
    {
        mpFsm->Finalize();

        delete mpFsm;
        mpFsm = nullptr;
    }

    mstAnimationDatas.clear();
}

/*----------*/
/* 更新 */
/*----------*/
void AnimationBase::Update()
{
    if (mpFsm != nullptr)
    {
        mpFsm->Update();
    }
}

/*----------*/
/* 現在ステート取得 */
/*----------*/
int AnimationBase::GetCurrentAnimationState() const
{
    if (mpFsm == nullptr)
    {
        return -1;
    }

    return mpFsm->GetCurrentState();
}

/*----------*/
/* 次ステート設定 */
/*----------*/
void AnimationBase::SetNextAnimationState(
    int state)
{
    if (mpFsm == nullptr)
    {
        return;
    }

    mpFsm->SetNextState(state);
}