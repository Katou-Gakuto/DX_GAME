#include <map>
#include <math.h>
#include <string>

#include "DxLib.h"

#include "AnimationEnum.h"
#include "AnimationData.h"

#include "AnimationBase.h"
#include "ModelBase.h"
#include "ModelsControllerBase.h"
#include "StateAnimation.h"
#include "StateBase.h"
#include "UtilCalc.h"

/*----------*/
/*【アニメーションステート共通処理】
/*----------*/

StateAnimationProcess::StateAnimationProcess(int modelHandle)
: mnModelHandle(modelHandle)
, mfAnimBlendRate(0.0f)
, mfAnimBlendSpeed(0.1f)
, mfAnimationSpeed(0.5f)
, meAnimationType(ANIMATION_TYPE::NONE)
{
    mstPreAnimationData.animationCount = 0.0f;
    mstPreAnimationData.animationHandle = -1;
    mstPreAnimationData.loopFlag = false;
}

// アニメーションをデタッチ
void StateAnimationProcess::AnimationDetach()
{
    if (mstPreAnimationData.animationHandle != (-1))
    {
        MV1DetachAnim(mnModelHandle, mstPreAnimationData.animationHandle);
        mstPreAnimationData.animationHandle = -1;
    }
}

// 現在の再生状況を保持しておく
void StateAnimationProcess::KeepAnimationData(AnimationBase* animation, std::map<ANIMATION_TYPE, AnimationDatas>* animationDatas)
{
    (*animationDatas)[animation->GetAnimationType()].preAnimationType = meAnimationType;
}
// TODO: 消す
// // 現在の再生状況も含めて破棄する
// void StateAnimationProcess::ClearAnimationData()
// {
//     for (int i = 0; i < MV_ONE_ANIMATION_NUMBER::MAX; i++)
//     {
//         mstMvOneAnimationDatas[i].animationCount = 0.0f;
//         mstMvOneAnimationDatas[i].animationHandle = -1;
//         mstMvOneAnimationDatas[i].loopFlag = false;
//     }
// }

// アニメーションをアタッチ
void StateAnimationProcess::AnimationAttach(AnimationBase* animation, AnimationDatas *nowAnimationData, std::map<ANIMATION_TYPE, AnimationDatas>* animationDatas)
{
    nowAnimationData->animationHandle = MV1AttachAnim(mnModelHandle, nowAnimationData->number);
    nowAnimationData->animationCount = 0.0f;
    meAnimationType = animation->GetAnimationType();

    mstPreAnimationData.animationHandle = (*animationDatas)[nowAnimationData->preAnimationType].animationHandle;
    mstPreAnimationData.animationCount = (*animationDatas)[nowAnimationData->preAnimationType].animationCount;

    mfAnimBlendRate = ((mstPreAnimationData.animationHandle == -1) ? 1.0f : 0.0f);
}

// アニメーション更新
void StateAnimationProcess::UpdateAnimation(AnimationDatas *nowAnimationData)
{
    if (mnModelHandle != -1) {

        // ブレンド率更新
        UpdateBlend();

        float animTotalTime;

        // 現在のアニメーション時間を進める
        AdvanceAnimationTime(nowAnimationData->animationHandle, &nowAnimationData->animationCount, nowAnimationData->loopFlag, mfAnimBlendRate);

        // 前のアニメーション時間を進める
        AdvanceAnimationTime(mstPreAnimationData.animationHandle, &mstPreAnimationData.animationCount, mstPreAnimationData.loopFlag, ANIMATION_BLEND_RATE_MAX - mfAnimBlendRate);

        // TODO: 消す
        // for (int i = 0; i < MV_ONE_ANIMATION_NUMBER::MAX; i++)
        // {
        //     if (mstMvOneAnimationDatas[i].animationHandle != -1)
        //     {
        //         // 総再生時間を取得
        //         animTotalTime = MV1GetAttachAnimTotalTime(mnModelHandle, mstMvOneAnimationDatas[i].animationHandle);

        //         // 再生時間を進める
        //         mstMvOneAnimationDatas[i].animationCount += mfAnimationSpeed;

        //         // ループさせる
        //         if (mstMvOneAnimationDatas[i].animationCount >= animTotalTime )
        //         {
        //             if (mstMvOneAnimationDatas[i].loopFlag)
        //             {
        //                 mstMvOneAnimationDatas[i].animationCount = fmodf(mstMvOneAnimationDatas[i].animationCount, animTotalTime);
        //             }
        //             else
        //             {
        //                 switch (i)
        //                 {
        //                 case MV_ONE_ANIMATION_NUMBER::NOW:
        //                     mstMvOneAnimationDatas[i].animationCount = animTotalTime;
        //                     break;
                        
        //                 case MV_ONE_ANIMATION_NUMBER::PRE:
        //                     mstMvOneAnimationDatas[i].animationCount -= mfAnimationSpeed;
        //                     break;
        //                 }
        //             }
        //         }

        //         // モデルに反映
        //         MV1SetAttachAnimTime(mnModelHandle, mstMvOneAnimationDatas[i].animationHandle, mstMvOneAnimationDatas[i].animationCount);

        //         // アニメーション反映率を設定
        //         switch (i)
        //         {
        //         case MV_ONE_ANIMATION_NUMBER::NOW:
        //             MV1SetAttachAnimBlendRate(mnModelHandle, mstMvOneAnimationDatas[i].animationHandle, mfAnimBlendRate);
        //             break;
        //         case MV_ONE_ANIMATION_NUMBER::PRE:
        //             MV1SetAttachAnimBlendRate(mnModelHandle, mstMvOneAnimationDatas[i].animationHandle, ANIMATION_BLEND_RATE_MAX - mfAnimBlendRate);
        //             break;
        //         }
        //     }
        // }
    }
}

void StateAnimationProcess::UpdateBlend()
{
    // ブレンド率を加算していく
    if (mfAnimBlendRate < ANIMATION_BLEND_RATE_MAX)
    {
        mfAnimBlendRate += mfAnimBlendSpeed;

        if (mfAnimBlendRate > ANIMATION_BLEND_RATE_MAX)
        {
            mfAnimBlendRate = ANIMATION_BLEND_RATE_MAX;
        }
    }
}

/*アニメーション時間を進める*/
void StateAnimationProcess::AdvanceAnimationTime(int animationHandle, float* animationCount, bool loopFlag, float animBlendRate)
{
    // アニメーション処理
    if (animationHandle != -1)
    {
        // 総再生時間を取得
        float animTotalTime = MV1GetAttachAnimTotalTime(mnModelHandle, animationHandle);

        // 再生時間を進める
        *animationCount += mfAnimationSpeed;

        // ループさせる
        if (*animationCount >= animTotalTime)
        {
            if (loopFlag)
            {
                *animationCount = fmodf(*animationCount, animTotalTime);
            }
            else
            {
                *animationCount = animTotalTime;
            }
        }

        // モデルに反映
        MV1SetAttachAnimTime(mnModelHandle, animationHandle, *animationCount);

        // アニメーション反映率を設定
        MV1SetAttachAnimBlendRate(mnModelHandle, animationHandle, animBlendRate);
    }
}

/*----------*/
/*【MV1モデルアニメーション】
/*----------*/

StateMVOneAnimation::StateMVOneAnimation(int modelHandle, std::string fileName)
: IStateAnimation()
, StateAnimationProcess(modelHandle)
{
    // アニメーションフレーム固定
    {
        // アニメーションで移動をしているフレームの番号を検索する
        int moveAnimFrameIndex = MV1SearchFrame(mnModelHandle, fileName.c_str());

        // アニメーションで移動しているフレームを無効にする
        MV1SetFrameUserLocalMatrix(mnModelHandle, moveAnimFrameIndex, MV1GetFrameLocalMatrix(mnModelHandle, moveAnimFrameIndex));
    }

    mStateNumber = MODEL_TYPE::MV1_MODEL;
}

// この状態に入った時の処理
void StateMVOneAnimation::OnEnter(AnimationBase* animation, AnimationDatas *nowAnimationData, std::map<ANIMATION_TYPE, AnimationDatas>* animationDatas, MODEL_TYPE oldModelType)
{
    AnimationAttach(animation, nowAnimationData, animationDatas);
}

// この状態を出る時の処理
void StateMVOneAnimation::OnExit(AnimationBase* animation, AnimationDatas *nowAnimationData, std::map<ANIMATION_TYPE, AnimationDatas>* animationDatas, MODEL_TYPE newModelType)
{
    AnimationDetach();

    // TODO: 関数化して同じ以外でも似た処理の場合対応できるようにしたい
    if (mStateNumber == newModelType)
    {
        KeepAnimationData(animation, animationDatas);
    }
    else if (CheckSimilarModelType(newModelType))
    {

    }
    else
    {
        ClearAnimationData();
    }
}

// 更新
void StateMVOneAnimation::Update(AnimationBase* animation, AnimationDatas *nowAnimationData)
{
    // アニメーション更新
    UpdateAnimation(nowAnimationData);
}

// モデル種類が同類なら「true」を返す
bool StateMVOneAnimation::CheckSimilarModelType(MODEL_TYPE modelType)
{
    switch (modelType)
    {
    case MODEL_TYPE::MV1_MODEL:
        return true;
    }

    return false;
}


/*----------*/
/*【MV1モデル　アニメーション無しモデル】
/*----------*/
StateMVOneOnlyAnimation::StateMVOneOnlyAnimation(int modelHandle)
: IStateAnimation()
, StateAnimationProcess(modelHandle)
{
    mStateNumber = MODEL_TYPE::MV1_MODEL_ONLY;
}

// この状態に入った時の処理
void StateMVOneOnlyAnimation::OnEnter(AnimationBase* animation, AnimationDatas *nowAnimationData, std::map<ANIMATION_TYPE, AnimationDatas>* animationDatas, MODEL_TYPE oldModelType)
{
    AnimationAttach(animation, nowAnimationData, animationDatas);
}

// この状態を出る時の処理
void StateMVOneOnlyAnimation::OnExit(AnimationBase* animation, AnimationDatas *nowAnimationData, std::map<ANIMATION_TYPE, AnimationDatas>* animationDatas, MODEL_TYPE newModelType)
{
    AnimationDetach();

    // TODO: 関数化して同じ以外でも似た処理の場合対応できるようにしたい
    if (mStateNumber == newModelType)
    {
        KeepAnimationData();
    }
    else if (CheckSimilarModelType(newModelType))
    {

    }
    else
    {
        ClearAnimationData();
    }
}

// 更新
void StateMVOneOnlyAnimation::Update(AnimationBase* animation, AnimationDatas *nowAnimationData)
{
    // アニメーション更新
    UpdateAnimation(nowAnimationData);
}

// モデル種類が同類なら「true」を返す
bool StateMVOneOnlyAnimation::CheckSimilarModelType(MODEL_TYPE modelType)
{
    switch (modelType)
    {
    case MODEL_TYPE::MV1_MODEL_MOVE:
    case MODEL_TYPE::MV1_MODEL_ONLY:
        return false;
    }

    return false;
}

// アニメーションをアタッチ
void StateMVOneOnlyAnimation::AnimationAttach(AnimationBase* animation, AnimationDatas *nowAnimationData, std::map<ANIMATION_TYPE, AnimationDatas>* animationDatas)
{
    nowAnimationData->animationHandle = MV1AttachAnim(mnModelHandle, 0, nowAnimationData->number, FALSE);
    nowAnimationData->animationCount = 0.0f;
    meAnimationType = animation->GetAnimationType();

    mstPreAnimationData.animationHandle = (*animationDatas)[nowAnimationData->preAnimationType].animationHandle;
    mstPreAnimationData.animationCount = (*animationDatas)[nowAnimationData->preAnimationType].animationCount;

    mfAnimBlendRate = ((mstPreAnimationData.animationHandle == -1) ? 1.0f : 0.0f);
}

/*----------*/
/*【MV1モデル モデル操作】
/*----------*/
StateMVOneOperationAnimation::StateMVOneOperationAnimation(int modelHandle, VECTOR changeVec, VECTOR changeAngle)
: StateMVOneOnlyAnimation(modelHandle)
, mvChangeMove(changeVec)
, mvMove(UtilCalc::VZero)
, mvChangeAngle(changeAngle)
, mvAngle(UtilCalc::VZero)
{
    mStateNumber = MODEL_TYPE::MV1_MODEL_MOVE;
}

// この状態に入った時の処理
void StateMVOneOperationAnimation::OnEnter(AnimationBase* animation, AnimationDatas *nowAnimationData, std::map<ANIMATION_TYPE, AnimationDatas>* animationDatas, MODEL_TYPE oldModelType)
{
    AnimationAttach(animation, nowAnimationData, animationDatas);

    mvMove = mpModelBase->GetPosition();;
    mvAngle = mpModelBase->GetAngle();;
}

// この状態を出る時の処理
void StateMVOneOperationAnimation::OnExit(AnimationBase* animation, AnimationDatas *nowAnimationData, std::map<ANIMATION_TYPE, AnimationDatas>* animationDatas, MODEL_TYPE newModelType)
{
    AnimationDetach();

    // TODO: 関数化して同じ以外でも似た処理の場合対応できるようにしたい
    if (mStateNumber == newModelType)
    {
        KeepAnimationData();
    }
    else if (CheckSimilarModelType(newModelType))
    {

    }
    else
    {
        ClearAnimationData();
    }
    
    mpModelBase->SetPosition(mvMove);
    mpModelBase->SetAngle(mvAngle);
}

// 更新
void StateMVOneOperationAnimation::Update(AnimationBase* animation, AnimationDatas *nowAnimationData)
{
    mpModelBase->SetPosition(VAdd(mpModelBase->GetPosition(), mvChangeMove));
    mpModelBase->SetAngle(VAdd(mpModelBase->GetAngle(), mvChangeAngle));
}

// モデル種類が同類なら「true」を返す
bool StateMVOneOperationAnimation::CheckSimilarModelType(MODEL_TYPE modelType)
{
    switch (modelType)
    {
    case MODEL_TYPE::MV1_MODEL_MOVE:
    case MODEL_TYPE::MV1_MODEL_ONLY:
        return false;
    }

    return false;
}