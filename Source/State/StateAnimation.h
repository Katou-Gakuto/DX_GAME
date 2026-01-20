#pragma once
#include <map>
#include <string>

#include "AnimationEnum.h"
#include "AnimationData.h"

#include "AnimationBase.h"
#include "ModelBase.h"
#include "StateBase.h"

/*----------*/
/*【アニメーションステート共通処理】
/*----------*/
class StateAnimationProcess
{
protected:
    // MV1アニメション情報
    struct MVOneAnimationData
    {
        float animationCount;   // アニメーションカウント
        int animationHandle;    // アニメションハンドル
        bool loopFlag;          // ループフラグ
    };

protected:
    // モデルハンドル
    int mnModelHandle;
    
    // 一つ前のアニメーション情報
    MVOneAnimationData mstPreAnimationData;

    // アニメーション種類
    ANIMATION_TYPE meAnimationType;

    // ブレンド率
    float mfAnimBlendRate;

    // ブレンド速度
    float mfAnimBlendSpeed;

    // 再生速度
    float mfAnimationSpeed;

    // ブレンド率最大
    const float ANIMATION_BLEND_RATE_MAX = 1.0f;
public:
    StateAnimationProcess(int handle);
    ~StateAnimationProcess() = default;

protected:
    /*アニメーションをデタッチ*/
    virtual void AnimationDetach();
    // TODO: 関数説明と関数名を変える
    /*現在の再生状況を保持しておく*/
    virtual void KeepAnimationData(AnimationBase* animation, std::map<ANIMATION_TYPE, AnimationDatas>* animationDatas);

    /*アニメーションをアタッチ*/
    virtual void AnimationAttach(AnimationBase* animation, AnimationDatas *nowAnimationData, std::map<ANIMATION_TYPE, AnimationDatas>* animationDatas);

    /*アニメーション更新*/
    void UpdateAnimation(AnimationDatas *nowAnimationData);

    /*ブレンド更新*/
    void UpdateBlend();

    /*アニメーション時間を進める*/
    void AdvanceAnimationTime(int animationHandle, float* animationCount, bool loopFlag, float animBlendRate);
};


/*----------*/
/*【MV1モデルアニメーション】
/*----------*/
class StateMVOneAnimation : public IStateAnimation, public StateAnimationProcess
{
public:
    StateMVOneAnimation(int modelHandle, std::string fileName);
    ~StateMVOneAnimation() = default;

    /// <summary>この状態に入った時の処理</summary>
    /// <param name="animation">アニメーション</param>
    /// <param name="animationDatas">アニメーション情報</param>
    virtual void OnEnter(AnimationBase* animation, AnimationDatas *nowAnimationData, std::map<ANIMATION_TYPE, AnimationDatas>* animationDatas, MODEL_TYPE oldModelType) override;
    /// <summary>この状態を出る時の処理</summary>
    /// <param name="animation">アニメーション</param>
    /// <param name="animationDatas">アニメーション情報</param>
    virtual void OnExit(AnimationBase* animation, AnimationDatas *nowAnimationData, std::map<ANIMATION_TYPE, AnimationDatas>* animationDatas, MODEL_TYPE newModelType) override;

    /// <summary>更新</summary>
    /// <param name="animation">アニメーション</param>
    /// <param name="animationDatas">アニメーション情報</param>
    virtual void Update(AnimationBase* animation, AnimationDatas *nowAnimationData) override;

private:
    /*モデル種類が同類なら「true」を返す*/
    bool CheckSimilarModelType(MODEL_TYPE modelType) override;
};

/*----------*/
/*【MV1モデル　アニメーション無しモデル】
/*----------*/
class StateMVOneOnlyAnimation : public IStateAnimation, public StateAnimationProcess
{
public:
    StateMVOneOnlyAnimation(int modelHandle);
    ~StateMVOneOnlyAnimation() = default;

    /// <summary>この状態に入った時の処理</summary>
    /// <param name="animation">アニメーション</param>
    /// <param name="animationDatas">アニメーション情報</param>
    virtual void OnEnter(AnimationBase* animation, AnimationDatas *nowAnimationData, std::map<ANIMATION_TYPE, AnimationDatas>* animationDatas, MODEL_TYPE oldModelType) override;
    /// <summary>この状態を出る時の処理</summary>
    /// <param name="animation">アニメーション</param>
    /// <param name="animationDatas">アニメーション情報</param>
    virtual void OnExit(AnimationBase* animation, AnimationDatas *nowAnimationData, std::map<ANIMATION_TYPE, AnimationDatas>* animationDatas, MODEL_TYPE newModelType) override;

    /// <summary>更新</summary>
    /// <param name="animation">アニメーション</param>
    /// <param name="animationDatas">アニメーション情報</param>
    virtual void Update(AnimationBase* animation, AnimationDatas *nowAnimationData) override;

protected:

    /*モデル種類が同類なら「true」を返す*/
    virtual bool CheckSimilarModelType(MODEL_TYPE modelType) override;

    /*アニメーションをアタッチ*/
    virtual void AnimationAttach(AnimationBase* animation, AnimationDatas *animationData, std::map<ANIMATION_TYPE, AnimationDatas>* animationDatas) override;
};


// HACK: 一つしかできないから複数できるようにアニメーションデータでやる
/*----------*/
/*【MV1モデル モデル操作】
/*----------*/
class StateMVOneOperationAnimation : public StateMVOneOnlyAnimation
{
private:
    // 変更移動量
    VECTOR mvChangeMove;
    // 移動量
    VECTOR mvMove;

    // 変更アングル量
    VECTOR mvChangeAngle;
    // アングル
    VECTOR mvAngle;

public:
    StateMVOneOperationAnimation(int modelHandle, VECTOR changeVec, VECTOR changeAngle);
    ~StateMVOneOperationAnimation() = default;

    /// <summary>この状態に入った時の処理</summary>
    /// <param name="animation">アニメーション</param>
    /// <param name="animationDatas">アニメーション情報</param>
    virtual void OnEnter(AnimationBase* animation, AnimationDatas *nowAnimationData, std::map<ANIMATION_TYPE, AnimationDatas>* animationDatas, MODEL_TYPE oldModelType) override;
    /// <summary>この状態を出る時の処理</summary>
    /// <param name="animation">アニメーション</param>
    /// <param name="animationDatas">アニメーション情報</param>
    virtual void OnExit(AnimationBase* animation, AnimationDatas *nowAnimationData, std::map<ANIMATION_TYPE, AnimationDatas>* animationDatas, MODEL_TYPE newModelType) override;

    /// <summary>更新</summary>
    /// <param name="animation">アニメーション</param>
    /// <param name="animationDatas">アニメーション情報</param>
    virtual void Update(AnimationBase* animation, AnimationDatas *nowAnimationData) override;


protected:
    /*モデル種類が同類なら「true」を返す*/
    virtual bool CheckSimilarModelType(MODEL_TYPE modelType) override;
};