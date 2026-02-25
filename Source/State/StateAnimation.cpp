#include <map>
#include <math.h>
#include <string>

#include "AnimationEnum.h"
#include "AnimationData.h"
#include "ResourceData.h"

#include "DxLib.h"

#include "Master.h"

#include "AnimationBase.h"
#include "ModelBase.h"
#include "ModelsControllerBase.h"
#include "ResourceManager.h"
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
, meAnimationType(ANIMATION_TYPE::IDLE)
{
    mstPreAnimationData.animationCount = 0.0f;
    mstPreAnimationData.animationHandle = -1;
    mstPreAnimationData.loopFlag = false;
}

// アニメーションをデタッチ
void StateAnimationProcess::AnimationDetach(AnimationBase* animation, AnimationDatas* animationDatas)
{
    if (mstPreAnimationData.animationHandle != (-1))
    {
        MV1DetachAnim(mnModelHandle, mstPreAnimationData.animationHandle);
        mstPreAnimationData.animationHandle = -1;
    }

    // 現在のステートと次のステートを紐づけて前のステートとして扱う
    animationDatas->animDatas[animation->GetAnimationType()].preAnimationType = meAnimationType;
}

// アニメーションをアタッチ
void StateAnimationProcess::AnimationAttach(AnimationBase* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas)
{
    nowAnimationData->animationHandle = MV1AttachAnim(mnModelHandle, nowAnimationData->number);
    nowAnimationData->animationCount = 0.0f;
}

// 一つ前のアニメーション情報を設定する
void StateAnimationProcess::PreAnimationDataSetting(AnimationBase* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas)
{
    if (nowAnimationData->preAnimationType != ANIMATION_TYPE::NONE)
    {
        meAnimationType = animation->GetAnimationType();

        mstPreAnimationData.animationHandle = animationDatas->animDatas[nowAnimationData->preAnimationType].animationHandle;
        mstPreAnimationData.animationCount = animationDatas->animDatas[nowAnimationData->preAnimationType].animationCount;
        mstPreAnimationData.loopFlag = animationDatas->animDatas[nowAnimationData->preAnimationType].loopFlag;

        mfAnimBlendRate = ((mstPreAnimationData.animationHandle == -1) ? 1.0f : 0.0f);
    }
}

// 初期化
void StateAnimationProcess::Init(AnimationBase* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas)
{
    // アタッチ
    AnimationAttach(animation, nowAnimationData, animationDatas);

    // 前のアニメーション情報を設定
    PreAnimationDataSetting(animation, nowAnimationData, animationDatas);
}

// アニメーション更新
void StateAnimationProcess::UpdateAnimation(OneAnimationData *nowAnimationData)
{
    if (mnModelHandle != -1) {

        // ブレンド率更新
        UpdateBlend();

        // 現在のアニメーション時間を進める
        AdvanceAnimationTime(nowAnimationData->animationHandle, &nowAnimationData->animationCount, nowAnimationData->loopFlag, mfAnimBlendRate, true);

        // 前のアニメーション時間を進める
        AdvanceAnimationTime(mstPreAnimationData.animationHandle, &mstPreAnimationData.animationCount, mstPreAnimationData.loopFlag, ANIMATION_BLEND_RATE_MAX - mfAnimBlendRate, true);
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
void StateAnimationProcess::AdvanceAnimationTime(int animationHandle, float* animationCount, bool loopFlag, float animBlendRate, bool testFlag)
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
                if (testFlag)
                {
                    *animationCount = animTotalTime;
                }
                else
                {
                    *animationCount -= mfAnimationSpeed;
                }
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
void StateMVOneAnimation::OnEnter(AnimationBase* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas, MODEL_TYPE oldModelType)
{
    Init(animation, nowAnimationData, animationDatas);
}

// この状態を出る時の処理
void StateMVOneAnimation::OnExit(AnimationBase* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas, MODEL_TYPE newModelType)
{
    AnimationDetach(animation, animationDatas);
}

// 終了
void StateMVOneAnimation::Finalize(AnimationBase* animation, AnimationDatas* animationDatas)
{
}

// 更新
void StateMVOneAnimation::Update(AnimationBase* animation, OneAnimationData *nowAnimationData)
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
void StateMVOneOnlyAnimation::OnEnter(AnimationBase* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas, MODEL_TYPE oldModelType)
{
    Init(animation, nowAnimationData, animationDatas);
}

// この状態を出る時の処理
void StateMVOneOnlyAnimation::OnExit(AnimationBase* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas, MODEL_TYPE newModelType)
{
    AnimationDetach(animation, animationDatas);
}

// 終了
void StateMVOneOnlyAnimation::Finalize(AnimationBase* animation, AnimationDatas* animationDatas)
{
    std::vector<ANIMATION_TYPE> deleteAnimationType;
    deleteAnimationType.clear();
    deleteAnimationType.reserve(animationDatas->animDatas.size());

    for (auto& animationData : animationDatas->animDatas)
    {
        if (animationData.second.number!= (-1))
        {
            deleteAnimationType.push_back(animationData.first);
            Master::mpResourceManager->ReduceModelHandle(animationData.second.number);
        }
    }

    if (deleteAnimationType.size() == animationDatas->animDatas.size())
    {
        animationDatas->animDatas.clear();
        return;
    }

    for (int i = 0; i < deleteAnimationType.size(); i++)
    {
        animationDatas->animDatas.erase(deleteAnimationType[i]);
    }
}

// 更新
void StateMVOneOnlyAnimation::Update(AnimationBase* animation, OneAnimationData *nowAnimationData)
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
        return true;
    }

    return false;
}

// アニメーションをアタッチ
void StateMVOneOnlyAnimation::AnimationAttach(AnimationBase* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas)
{
    nowAnimationData->animationHandle = MV1AttachAnim(mnModelHandle, 0, nowAnimationData->number, FALSE);
    nowAnimationData->animationCount = 0.0f;
}

/*----------*/
/*【MV1モデル モデル操作】
/*----------*/
StateMVOneOperationAnimation::StateMVOneOperationAnimation(int modelHandle, VECTOR changeVec, VECTOR changeAngle, VECTOR changeSize)
: StateMVOneOnlyAnimation(modelHandle)
, mvChangeMove(changeVec)
, mvMove(UtilCalc::VZero)
, mvChangeAngle(changeAngle)
, mvAngle(UtilCalc::VZero)
, mvChangeSize(changeSize)
, mvSize(UtilCalc::VZero)
{
    mStateNumber = MODEL_TYPE::MV1_MODEL_MOVE;
}

// この状態に入った時の処理
void StateMVOneOperationAnimation::OnEnter(AnimationBase* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas, MODEL_TYPE oldModelType)
{
    Init(animation, nowAnimationData, animationDatas);

    mvMove  = UtilCalc::VZero;
    mvAngle = UtilCalc::VZero;
    mvSize  = UtilCalc::VZero;
}

// この状態を出る時の処理
void StateMVOneOperationAnimation::OnExit(AnimationBase* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas, MODEL_TYPE newModelType)
{
    AnimationDetach(animation, animationDatas);

    mpModelBase->SetPosition( VSub(mpModelBase->GetPosition(), mvMove));
    mpModelBase->SetAngle(    VSub(mpModelBase->GetAngle(),    mvAngle));
    mpModelBase->SetSize(     VSub(mpModelBase->GetSize(),     mvSize));
}

// 更新
void StateMVOneOperationAnimation::Update(AnimationBase* animation, OneAnimationData *nowAnimationData)
{
    mvMove  = VAdd(mvMove,  mvChangeMove);
    mvAngle = VAdd(mvAngle, mvChangeAngle);
    mvSize  = VAdd(mvSize,  mvChangeSize);

    mpModelBase->SetPosition( VAdd(mpModelBase->GetPosition(), mvChangeMove));
    mpModelBase->SetAngle(    VAdd(mpModelBase->GetAngle(),    mvChangeAngle));
    mpModelBase->SetSize(     VAdd(mpModelBase->GetSize(),     mvChangeSize));
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

/*----------*/
/*【エフェクトアニメーション】
/*----------*/

StateEffectAnimation::StateEffectAnimation(int* effectHandle)
: IStateAnimation()
, mnEffectHandle(effectHandle)
{
    mStateNumber = MODEL_TYPE::EFFECT;
}

// この状態に入った時の処理
void StateEffectAnimation::OnEnter(AnimationBase* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas, MODEL_TYPE oldModelType)
{
    if (!mpModelBase->GetDrawFlag())
    {
        return;
    }

    *mnEffectHandle = Master::mpResourceManager->GetEffectHandle(nowAnimationData->number, *mnEffectHandle);
}

// この状態を出る時の処理
void StateEffectAnimation::OnExit(AnimationBase* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas, MODEL_TYPE newModelType)
{
    if (*mnEffectHandle != -1)
    {
        return;
    }

    Master::mpResourceManager->DeletePlayEffectHandle(*mnEffectHandle);
    *mnEffectHandle = -1;
}

// 終了
void StateEffectAnimation::Finalize(AnimationBase* animation, AnimationDatas* animationDatas)
{
    std::vector<ANIMATION_TYPE> deleteAnimationType;
    deleteAnimationType.clear();
    deleteAnimationType.reserve(animationDatas->animDatas.size());

    for (auto& animationData : animationDatas->animDatas)
    {
        if (animationData.second.number != (-1))
        {
            deleteAnimationType.push_back(animationData.first);
            Master::mpResourceManager->ReduceEffectDataHandle(animationData.second.number);
        }
    }

    if (deleteAnimationType.size() == animationDatas->animDatas.size())
    {
        animationDatas->animDatas.clear();
        return;
    }

    for (int i = 0; i < deleteAnimationType.size(); i++)
    {
        animationDatas->animDatas.erase(deleteAnimationType[i]);
    }
}

// 更新
void StateEffectAnimation::Update(AnimationBase* animation, OneAnimationData *nowAnimationData)
{
}

// モデル種類が同類なら「true」を返す
bool StateEffectAnimation::CheckSimilarModelType(MODEL_TYPE modelType)
{
    return false;
}

/*----------*/
/*【画像アニメーション】
/*----------*/
StateGraphAnimation::StateGraphAnimation()
: IStateAnimation()
{
    mStateNumber = MODEL_TYPE::GRAPH;
}

// この状態に入った時の処理
void StateGraphAnimation::OnEnter(AnimationBase* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas, MODEL_TYPE oldModelType)
{
}

// この状態を出る時の処理
void StateGraphAnimation::OnExit(AnimationBase* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas, MODEL_TYPE newModelType)
{
}

// 終了
void StateGraphAnimation::Finalize(AnimationBase* animation, AnimationDatas* animationDatas)
{
}

// 更新
void StateGraphAnimation::Update(AnimationBase* animation, OneAnimationData *nowAnimationData)
{
}

// モデル種類が同類なら「true」を返す
bool StateGraphAnimation::CheckSimilarModelType(MODEL_TYPE modelType)
{
    return false;
}

/*----------*/
/*【動画アニメーション】
/*----------*/
StateMovieAnimation::StateMovieAnimation()
: IStateAnimation()
{
    mStateNumber = MODEL_TYPE::MOVIE;
}

// この状態に入った時の処理
void StateMovieAnimation::OnEnter(AnimationBase* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas, MODEL_TYPE oldModelType)
{
}

// この状態を出る時の処理
void StateMovieAnimation::OnExit(AnimationBase* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas, MODEL_TYPE newModelType)
{
}

// 終了
void StateMovieAnimation::Finalize(AnimationBase* animation, AnimationDatas* animationDatas)
{
}

// 更新
void StateMovieAnimation::Update(AnimationBase* animation, OneAnimationData *nowAnimationData)
{
}

// モデル種類が同類なら「true」を返す
bool StateMovieAnimation::CheckSimilarModelType(MODEL_TYPE modelType)
{
    return false;
}


/*------------------------------*/
/*【フェード画像アニメーション】*/
/*------------------------------*/
StateFadeGraphAnimation::StateFadeGraphAnimation()
: IStateAnimation()
{
    mStateNumber = MODEL_TYPE::FADE;
}

// この状態に入った時の処理
void StateFadeGraphAnimation::OnEnter(AnimationBase* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas, MODEL_TYPE oldModelType)
{
    DrawConfigData drawConfigData = mpModelBase->GetDrawConfigData();

    if (drawConfigData.blendMode != DX_BLENDMODE_ALPHA)
    {
        drawConfigData.blendMode = DX_BLENDMODE_ALPHA;
        if (nowAnimationData->blendParameter > 0)
        {
            drawConfigData.blendParameter = 0;
        }
        else
        {
            drawConfigData.blendParameter = 255;
        }
        mpModelBase->SetDrawConfigData(drawConfigData);
    }
}

// この状態を出る時の処理
void StateFadeGraphAnimation::OnExit(AnimationBase* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas, MODEL_TYPE newModelType)
{
}

// 終了
void StateFadeGraphAnimation::Finalize(AnimationBase* animation, AnimationDatas* animationDatas)
{
}

// 更新
void StateFadeGraphAnimation::Update(AnimationBase* animation, OneAnimationData *nowAnimationData)
{
    FadeProcess(nowAnimationData);
}

// フェード処理
void StateFadeGraphAnimation::FadeProcess(OneAnimationData *nowAnimationData)
{
    // 描画情報を取得し変更する
    DrawConfigData drawConfigData = mpModelBase->GetDrawConfigData();
    drawConfigData.blendParameter += nowAnimationData->blendParameter;


    // 描画情報が範囲外なら修正する
    if (drawConfigData.blendParameter > 255)
    {
        drawConfigData.blendParameter = 255;  
    }
    else if (drawConfigData.blendParameter < 0)
    {
        drawConfigData.blendParameter = 0;    
    }

    // 変更した描画情報を設定
    mpModelBase->SetDrawConfigData(drawConfigData); 
}

// モデル種類が同類なら「true」を返す
bool StateFadeGraphAnimation::CheckSimilarModelType(MODEL_TYPE modelType)
{
    return false;
}

/*----------*/
/*【DOTweenアニメーション】*/
/*----------*/
StateDOTweenAnimation::StateDOTweenAnimation()
: IStateAnimation()
{
    mStateNumber = MODEL_TYPE::TOD_WEEN;
}

// この状態に入った時の処理
void StateDOTweenAnimation::OnEnter(AnimationBase* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas, MODEL_TYPE oldModelType)
{
    // 数字設定
}

// この状態を出る時の処理
void StateDOTweenAnimation::OnExit(AnimationBase* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas, MODEL_TYPE newModelType)
{
}

// 終了
void StateDOTweenAnimation::Finalize(AnimationBase* animation, AnimationDatas* animationDatas)
{
}

// 更新
void StateDOTweenAnimation::Update(AnimationBase* animation, OneAnimationData *nowAnimationData)
{
}

// モデル種類が同類なら「true」を返す
bool StateDOTweenAnimation::CheckSimilarModelType(MODEL_TYPE modelType)
{
    return false;
}