#include "FSMAnimation.h"

FSMAnimation::FSMAnimation()
    : FSMBase()
{
}

/*----------*/
/* ‰Šú‰» */
/*----------*/
void FSMAnimation::Initilize(
    AnimationBase* animation,
    OneAnimationData* oneAnimationData,
    AnimationDatas* animationDatas)
{
    mStateAnimationData.StateAnimation =
        animation;

    mStateAnimationData.StateOneAnimationData =
        oneAnimationData;

    mStateAnimationData.StateAnimationDatas =
        animationDatas;

    if (mCurrentState != -1)
    {
        mmStateMap[mCurrentState]->OnEnter(
            &mStateAnimationData,
            mPreState);
    }
}

/*----------*/
/* I—¹ */
/*----------*/
void FSMAnimation::Finalize()
{
    for (auto& state : mmStateMap)
    {
        state.second->Finalize(
            &mStateAnimationData);
    }
}

/*----------*/
/* XV */
/*----------*/
void FSMAnimation::Update()
{
    CheckChangeState(
        &mStateAnimationData);

    auto itr = mmStateMap.find(mCurrentState);
    if (itr == mmStateMap.end())
    {
        return;
    }

    itr->second->Update(
        &mStateAnimationData);

}