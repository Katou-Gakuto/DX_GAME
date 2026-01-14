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

StateMVOneAnimation::StateMVOneAnimation(int modelHandle, std::string frameName)
: IStateAnimation()
, mnModelHandle(modelHandle)
, mfAnimBlendRate(0.0f)
, mfAnimBlendSpeed(0.1f)
, mfAnimationSpeed(0.5f)
{
    // アニメーションフレーム固定
    {
        // アニメーションで移動をしているフレームの番号を検索する
        int moveAnimFrameIndex = MV1SearchFrame(mnModelHandle, frameName.c_str());

        // アニメーションで移動しているフレームを無効にする
        MV1SetFrameUserLocalMatrix(mnModelHandle, moveAnimFrameIndex, MV1GetFrameLocalMatrix(mnModelHandle, moveAnimFrameIndex));
    }

    for (int i = 0; i < MV_ONE_ANIMATION_NUMBER::MAX; i++)
    {
        mstMvOneAnimationDatas[i].animationCount = 0.0f;
        mstMvOneAnimationDatas[i].animationHandle = -1;
        mstMvOneAnimationDatas[i].loopFlag = false;
    }

    mStateNumber = MODEL_TYPE::MV1_MODEL;
}

// この状態に入った時の処理
void StateMVOneAnimation::OnEnter(AnimationBase* animation, AnimationDatas animationDatas, MODEL_TYPE newModelType)
{
    AnimationAttach(animationDatas);
}

// この状態を出る時の処理
void StateMVOneAnimation::OnExit(AnimationBase* animation, AnimationDatas animationDatas, MODEL_TYPE oldModelType)
{
    AnimationDetach();

    // TODO: 関数化して同じ以外でも似た処理の場合対応できるようにしたい
    if (mStateNumber == oldModelType)
    {
        KeepAnimationData();
    }
    else
    {
        ClearAnimationData();
    }
}

// 更新
void StateMVOneAnimation::Update(AnimationBase* animation, AnimationDatas animationDatas)
{
    // アニメーション更新
    UpdateAnimation();
}

// アニメーションをデタッチ
void StateMVOneAnimation::AnimationDetach()
{
    if (mstMvOneAnimationDatas[MV_ONE_ANIMATION_NUMBER::PRE].animationHandle != (-1))
    {
        MV1DetachAnim(mnModelHandle, mstMvOneAnimationDatas[MV_ONE_ANIMATION_NUMBER::PRE].animationHandle);
        mstMvOneAnimationDatas[MV_ONE_ANIMATION_NUMBER::PRE].animationHandle = -1;
    }
}

// 現在の再生状況を保持しておく
void StateMVOneAnimation::KeepAnimationData()
{
    mstMvOneAnimationDatas[MV_ONE_ANIMATION_NUMBER::PRE] = mstMvOneAnimationDatas[MV_ONE_ANIMATION_NUMBER::NOW];
}

// 現在の再生状況も含めて破棄する
void StateMVOneAnimation::ClearAnimationData()
{
    for (int i = 0; i < MV_ONE_ANIMATION_NUMBER::MAX; i++)
    {
        mstMvOneAnimationDatas[i].animationCount = 0.0f;
        mstMvOneAnimationDatas[i].animationHandle = -1;
        mstMvOneAnimationDatas[i].loopFlag = false;
    }
}

// アニメーションをアタッチ
void StateMVOneAnimation::AnimationAttach(AnimationDatas animationData)
{
    mstMvOneAnimationDatas[MV_ONE_ANIMATION_NUMBER::NOW].animationHandle = MV1AttachAnim(mnModelHandle, animationData.number);
    mstMvOneAnimationDatas[MV_ONE_ANIMATION_NUMBER::NOW].animationCount = 0.0f;
    mstMvOneAnimationDatas[MV_ONE_ANIMATION_NUMBER::NOW].loopFlag = animationData.loopFlag;

    mfAnimBlendRate = ((mstMvOneAnimationDatas[MV_ONE_ANIMATION_NUMBER::PRE].animationHandle == -1) ? 1.0f : 0.0f);
}

// アニメーション更新
void StateMVOneAnimation::UpdateAnimation()
{
    if (mnModelHandle != -1) {

        // ブレンド率を加算していく
        if (mfAnimBlendRate < ANIMATION_BLEND_RATE_MAX)
        {
            mfAnimBlendRate += mfAnimBlendSpeed;

            if (mfAnimBlendRate > ANIMATION_BLEND_RATE_MAX)
            {
                mfAnimBlendRate = ANIMATION_BLEND_RATE_MAX;
            }
        }
        float animTotalTime;

        // アニメーション処理

        for (int i = 0; i < MV_ONE_ANIMATION_NUMBER::MAX; i++)
        {
            if (mstMvOneAnimationDatas[i].animationHandle != -1)
            {
                // 総再生時間を取得
                animTotalTime = MV1GetAttachAnimTotalTime(mnModelHandle, mstMvOneAnimationDatas[i].animationHandle);

                // 再生時間を進める
                mstMvOneAnimationDatas[i].animationCount += mfAnimationSpeed;

                // ループさせる
                if (mstMvOneAnimationDatas[i].animationCount >= animTotalTime )
                {
                    if (mstMvOneAnimationDatas[i].loopFlag)
                    {
                        mstMvOneAnimationDatas[i].animationCount = fmodf(mstMvOneAnimationDatas[i].animationCount, animTotalTime);
                    }
                    else
                    {
                        switch (i)
                        {
                        case MV_ONE_ANIMATION_NUMBER::NOW:
                            mstMvOneAnimationDatas[i].animationCount = animTotalTime;
                            break;
                        
                        case MV_ONE_ANIMATION_NUMBER::PRE:
                            mstMvOneAnimationDatas[i].animationCount -= mfAnimationSpeed;
                            break;
                        }
                    }
                }

                // モデルに反映
                MV1SetAttachAnimTime(mnModelHandle, mstMvOneAnimationDatas[i].animationHandle, mstMvOneAnimationDatas[i].animationCount);

                // アニメーション反映率を設定
                switch (i)
                {
                case MV_ONE_ANIMATION_NUMBER::NOW:
                    MV1SetAttachAnimBlendRate(mnModelHandle, mstMvOneAnimationDatas[i].animationHandle, mfAnimBlendRate);
                    break;
                case MV_ONE_ANIMATION_NUMBER::PRE:
                    MV1SetAttachAnimBlendRate(mnModelHandle, mstMvOneAnimationDatas[i].animationHandle, ANIMATION_BLEND_RATE_MAX - mfAnimBlendRate);
                    break;
                }
            }
        }
    }
}

//     if (index == -1) {
//         return;
//     }
//     if (mnModelHandle != -1) {
//         if (index != mnAnimNumber1)
//         {
//             // 前のアニメーションナンバーを保持
//             mnAnimNumber2 = mnAnimNumber1;
//             // 現在のアニメーションナンバーを保持
//             mnAnimNumber1 = index;

//             // 再生中のアニメーション2が有効状態だったらデタッチしておく
//             if (mnAnimation2 != (-1))
//             {

//                 MV1DetachAnim(mnModelHandle, mnAnimation2);
//                 mnAnimation2 = -1;
//             }

//             // 今まで再生されていた情報を2の方に保持しておく
//             mnAnimation2 = mnAnimation1;
//             mfAnimCount2 = mfAnimCount1;
//             mbLoopFlag2 = mbLoopFlag1;

//             // 新しいアニメーションアタッチして、アタッチ番号を保持しておく
//             if (!mbNotOneAnimFlag) {
//                 mnAnimation1 = MV1AttachAnim(mnModelHandle, index);
//             }
//             else {
//                 mnAnimation1 = MV1AttachAnim(mnModelHandle, 0, mnAnimHandle[mnAnimNumber1], FALSE);/*フレーム名が違くてもアタッチするようにしてる*/
//             }
//             mfAnimCount1 = 0.0f;

//             // 新しいアニメーションがループするかどうか
//             mbLoopFlag1 = LoopCheck(index);

//             // ブレンド率の初期値を設定
//             // note: アニメーション2が有効でない場合はブレンドさせないので1.0にしておく  
//             mfAnimBlendRate = (mnAnimation2 == -1 ? 1.0f : 0.0f);
//         }
//     }


//     if (mnModelHandle != -1) {

//         // ブレンド率を加算していく
//         if (mfAnimBlendRate < 1.0f)
//         {
//             mfAnimBlendRate += CHARA_ANIM_BLEND_SPEED;

//             if (mfAnimBlendRate > 1.0f)
//             {
//                 mfAnimBlendRate = 1.0f;
//             }
//         }
//         float fAnimTotalTime;

//         // アニメーション1の処理
//         if (mnAnimation1 != -1)
//         {
//             // 総再生時間を取得
//             fAnimTotalTime = MV1GetAttachAnimTotalTime(mnModelHandle, mnAnimation1);
            
//             // 再生時間を進める
//             mfAnimCount1 += CHARA_PLAY_ANIM_SPEED;

//             // ループさせる
//             if (mfAnimCount1 >= fAnimTotalTime && mbLoopFlag1)
//             {
//                 ///
//                 mfAnimCount1 = fmodf(mfAnimCount1, fAnimTotalTime);
//                 ///
//             }
//             else if (mfAnimCount1 >= fAnimTotalTime && !mbLoopFlag1)
//             {
//                 mfAnimCount1 = fAnimTotalTime;
//             }

//             // モデルに反映
//             MV1SetAttachAnimTime(mnModelHandle, mnAnimation1, mfAnimCount1);

//             // アニメーション反映率を設定
//             MV1SetAttachAnimBlendRate(mnModelHandle, mnAnimation1, mfAnimBlendRate);
//         }

        
//         // アニメーション2の処理
//         if (mnAnimation2 != -1)
//         {
//             // 総再生時間を取得
//             fAnimTotalTime = MV1GetAnimTotalTime(mnModelHandle, mnAnimation2);

//             // 再生時間を進める
//             mfAnimCount2 += CHARA_PLAY_ANIM_SPEED;

//             // ループさせる
//             if (mfAnimCount2 >= fAnimTotalTime && mbLoopFlag2)
//             {
//                 ///
//                 mfAnimCount2 = fmodf(mfAnimCount2, fAnimTotalTime);
//                 ///
//             }
//             else if (mfAnimCount2 >= fAnimTotalTime && !mbLoopFlag2)
//             {
//                 mfAnimCount2 -= CHARA_PLAY_ANIM_SPEED;
//             }


//             // モデルに反映
//             MV1SetAttachAnimTime(mnModelHandle, mnAnimation2, mfAnimCount2);

//             // アニメーション反映率を設定
//             MV1SetAttachAnimBlendRate(mnModelHandle, mnAnimation2, 1.0f - mfAnimBlendRate);
//         }
//     }
// }