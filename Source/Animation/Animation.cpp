#include "StateData.h"

#include "Animation.h"
#include "FSMAnimation.h"
#include "ModelBase.h"

Animation::Animation()
: mpFsm(nullptr)
, mpModel(nullptr)
, mstStateData()
{
}

// 初期化
void Animation::Initilize(ModelBase* model)
{
    mpModel = model;
}

// シーン最終初期化
void Animation::SceneLastInitilize()
{
    mpFsm->StateInitilize(&mstStateData);
}

// 終了
void Animation::Finalize()
{
    mpFsm->Finalize(&mstStateData);
}

// アニメーション更新
void Animation::Update()
{
    mpFsm->Update(&mstStateData);
}

// #include "AnimationBase.h"

// #include "FSMAnimation.h"

// AnimationBase::AnimationBase()
// : mpModelsController(nullptr)
// {
//     mmAnimationTime.clear();
    
//     mstAnimationDatas.clear();
//     mpFsm = nullptr;
// }

// // 初期化
// void AnimationBase::Initilize()
// {
//     if (mpFsm != nullptr)
//     {
//         mpFsm->Initilize(this);
//     }
// }

// // シーン最終初期化
// void AnimationBase::SceneLastInitilize()
// {
//     Update();
// }

// // 終了
// void AnimationBase::Finalize()
// {
//     if (mpFsm != nullptr)
//     {
//         mpFsm->Finalize(this);

//         delete mpFsm;
//     }

//     mstAnimationDatas.clear();
// }

// // アニメーション更新テスト
// void AnimationBase::Update()
// {
//     if (mpFsm != nullptr)
//     {
//         mpFsm->Update(this, mstAnimationDatas);
//     }
// }