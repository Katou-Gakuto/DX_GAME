#pragma once
#include <map>

#include "AnimationEnum.h"
#include "AnimationData.h"

#include "AnimationBase.h"
#include "ModelBase.h"
#include "StateBase.h"


class StateMVOneAnimation : public IStateAnimation
{
protected:
    // MV1アニメション情報
    struct MVOneAnimationData
    {
        float animationCount;   // アニメーションカウント
        int animationHandle;    // アニメションハンドル
    };

    // アニメーションのナンバー
    enum MV_ONE_ANIMATION_NUMBER
    {
        PRE = 0,    // 前のアニメーション
        NOW,        // 今のアニメーション
        MAX
    };

protected:
    // 前のアニメーション再生タイム
    int mnPreAnimNumber = -1;//???????

    // モデルハンドル
    int mnModelHandle;
    
    // MV1のアニメーション情報
    MVOneAnimationData mstMvOneAnimationDatas[MV_ONE_ANIMATION_NUMBER::MAX];

    // ブレンド率
    float mfAnimBlendRate;

    // ブレンド速度
    float mfAnimBlendSpeed;

    // 再生速度
    float mfAnimationSpeed;

    // ブレンド率最大
    const float ANIMATION_BLEND_RATE_MAX = 1.0f;

public:
    StateMVOneAnimation(int modelHandle);
    ~StateMVOneAnimation() = default;

    /// <summary>この状態に入った時の処理</summary>
    /// <param name="animation">アニメーション</param>
    /// <param name="animationDatas">アニメーション情報</param>
    /// <param name="model">モデル</param>
    /// <param name="animationStateData">アニメーションステート情報</param>
    void OnEnter(AnimationBase* animation, AnimationData& animationDatas, ModelBase* model, AnimationStateData& animationStateData) override;
    /// <summary>この状態を出る時の処理</summary>
    /// <param name="animation">アニメーション</param>
    /// <param name="animationDatas">アニメーション情報</param>
    /// <param name="model">モデル</param>
    void OnExit(AnimationBase* animation, AnimationData& animationDatas, ModelBase* model, AnimationStateData& animationStateData) override;

    /// <summary>更新</summary>
    /// <param name="animation">アニメーション</param>
    /// <param name="animationDatas">アニメーション情報</param>
    /// <param name="model">モデル</param>
    void Update(AnimationBase* animation, AnimationData& animationDatas, ModelBase* model, AnimationStateData& animationStateData) override;

protected:
    // アニメーションをデタッチ
    virtual void AnimationDetach();
    // 現在の再生状況を保持しておく
    virtual void KeepAnimationData();
    // 現在の再生状況も含めて破棄する
    virtual void ClearAnimationData();

    // アニメーションをアタッチ
    virtual void AnimationAttach(AnimationData& animationDatas);

    // アニメーション更新
    virtual void UpdateAnimation(ANIMATION_TYPE animationType);    
};