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
    if (mpFsm == nullptr)
    {
        return;
    }

    mstStateData.animation = this;
    mpFsm->StateInitilize(&mstStateData);
}

// 終了
void Animation::Finalize()
{
    if (mpFsm != nullptr)
    {
        mpFsm->Finalize(&mstStateData);
        delete mpFsm;
        mpFsm = nullptr;
    }
}

// ?A?j???[?V?????X?V
void Animation::Update()
{
    if (mpFsm != nullptr)
    {
        mpFsm->Update(&mstStateData);
    }
}

// ????A?j???[?V???????[?u???
void Animation::NextAnimationMoveSetting(ANIMATION_MOVE_TYPE animatioMoveType)
{
    if (mpFsm != nullptr)
    {
        mpFsm->SetNextAnimationMove(animatioMoveType);
    }
}


// #include "Animation.h"

// #include "FSMAnimation.h"

// Animation::Animation()
// : mpModelsController(nullptr)
// {
//     mmAnimationTime.clear();
    
//     mstAnimationDatas.clear();
//     mpFsm = nullptr;
// }

// // ??????
// void Animation::Initilize()
// {
//     if (mpFsm != nullptr)
//     {
//         mpFsm->Initilize(this);
//     }
// }

// // ?V?[????I??????
// void Animation::SceneLastInitilize()
// {
//     Update();
// }

// // ?I??
// void Animation::Finalize()
// {
//     if (mpFsm != nullptr)
//     {
//         mpFsm->Finalize(this);

//         delete mpFsm;
//     }

//     mstAnimationDatas.clear();
// }

// // ?A?j???[?V?????X?V?e?X?g
// void Animation::Update()
// {
//     if (mpFsm != nullptr)
//     {
//         mpFsm->Update(this, mstAnimationDatas);
//     }
// }