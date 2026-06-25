#pragma once
#include <map>
#include <string>

#include "AnimationEnum.h"
#include "AnimationData.h"

#include "AnimationBase.h"
#include "ModelBase.h"
#include "StateAnimationBase.h"
#include "UtilCalc.h"
// TODO: 3Dアニメーションと2Dアニメーションで分ける ステート設定時ナンバー設定

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
    // // モデルハンドル
    // int mnModelHandle;
    
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
    virtual void AnimationDetach(AnimationBase* animation, AnimationDatas* animationDatas);

    /*アニメーションをアタッチ*/
    virtual void AnimationAttach(AnimationBase* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas);

    /*一つ前のアニメーション情報を設定する*/
    virtual void PreAnimationDataSetting(AnimationBase* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas);

    /*アニメーション初期化*/
    virtual void Init(AnimationBase* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas);

    /*アニメーション更新*/
    void UpdateAnimation(OneAnimationData *nowAnimationData);

    /*ブレンド更新*/
    void UpdateBlend();

    /*アニメーション時間を進める*/
    void AdvanceAnimationTime(int animationHandle, float* animationCount, bool loopFlag, float animBlendRate, bool testFlag);
};

/*----------*/
/*【アニメーション無し】
/*----------*/
class StateNoneAnimation : public IStateAnimation
{
public:
    StateNoneAnimation(std::vector<STATE_CHANGE_CRITERIA_DATA<int, STATE_ANEMATION_DATA>> stateChangeCriterias);
    ~StateNoneAnimation() = default;

    /// <summary>この状態に入った時の処理(何もしない)</summary>
    /// <param name="animationData">アニメーション情報</param>
    /// <param name="preState">アニメーション種類</param>
    //virtual void OnEnter(STATE_ANEMATION_DATA* animationData, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas, MODEL_TYPE oldModelType) override {}
    virtual void OnEnter(STATE_ANEMATION_DATA* animationData, ANIMATION_TYPE preState) override {}
    /// <summary>この状態を出る時の処理(何もしない)</summary>
    /// <param name="animationData">アニメーション情報</param>
    /// <param name="nextState">次のアニメーション種類</param>
    //virtual void OnExit(AnimationBase* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas, MODEL_TYPE newModelType) override {}
    virtual void OnExit(STATE_ANEMATION_DATA* animationData, ANIMATION_TYPE nextState) override {}

    /// <summary>終了</summary>
    virtual void Finalize(AnimationBase* animation, AnimationDatas* animationDatas) override {}

    /// <summary>更新(何もしない)</summary>
    /// <param name="animation">アニメーション</param>
    /// <param name="animationDatas">アニメーション情報</param>
    virtual void Update(AnimationBase* animation, OneAnimationData *nowAnimationData) override {}

private:
    /*モデル種類が同類なら「true」を返す*/
    bool CheckSimilarModelType(MODEL_TYPE modelType) override { return false; }

};


/*----------*/
/*【MV1モデルアニメーション】
/*----------*/
class StateMVOneAnimation : public IStateAnimation, public StateAnimationProcess
{
public:
    // FIXME: コンストラクタでステート変更条件を渡せます
    StateMVOneAnimation(int modelHandle, std::string fileName, std::vector<STATE_CHANGE_CRITERIA_DATA<int, STATE_ANEMATION_DATA>> stateChangeCriterias);
    ~StateMVOneAnimation() = default;

   /// <summary>この状態に入った時の処理</summary>
    /// <param name="animationData">アニメーション情報</param>
    /// <param name="preState">アニメーション種類</param>
    virtual void OnEnter(STATE_ANEMATION_DATA* animationData, ANIMATION_TYPE preState) override;
  /// <summary>この状態を出る時の処理</summary>
    /// <param name="animationData">アニメーション情報</param>
    /// <param name="nextState">次のアニメーション種類</param>
    virtual void OnExit(STATE_ANEMATION_DATA* animationData, ANIMATION_TYPE nextState) override;

    /// <summary>終了</summary>
    virtual void Finalize(AnimationBase* animation, AnimationDatas* animationDatas) override;

    /// <summary>更新</summary>
    /// <param name="animation">アニメーション</param>
    /// <param name="animationDatas">アニメーション情報</param>
    virtual void Update(AnimationBase* animation, OneAnimationData *nowAnimationData) override;

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
    // FIXME: コンストラクタでステート変更条件を渡せます
    StateMVOneOnlyAnimation(int modelHandle, std::vector<STATE_CHANGE_CRITERIA_DATA<int, STATE_ANEMATION_DATA>> stateChangeCriterias);
    ~StateMVOneOnlyAnimation() = default;

   /// <summary>この状態に入った時の処理</summary>
    /// <param name="animationData">アニメーション情報</param>
    /// <param name="preState">アニメーション種類</param>
    virtual void OnEnter(STATE_ANEMATION_DATA* animationData, ANIMATION_TYPE preState) override;
  /// <summary>この状態を出る時の処理</summary>
    /// <param name="animationData">アニメーション情報</param>
    /// <param name="nextState">次のアニメーション種類</param>
    virtual void OnExit(STATE_ANEMATION_DATA* animationData, ANIMATION_TYPE nextState) override;

    /// <summary>終了</summary>
    virtual void Finalize(AnimationBase* animation, AnimationDatas* animationDatas) override;

    /// <summary>更新</summary>
    /// <param name="animation">アニメーション</param>
    /// <param name="animationDatas">アニメーション情報</param>
    virtual void Update(AnimationBase* animation, OneAnimationData *nowAnimationData) override;

protected:

    /*モデル種類が同類なら「true」を返す*/
    virtual bool CheckSimilarModelType(MODEL_TYPE modelType) override;

    /*アニメーションをアタッチ*/
    virtual void AnimationAttach(AnimationBase* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas) override;
};


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

    
    // 大きさ変更量
    VECTOR mvChangeSize;
    // 大きさ
    VECTOR mvSize;

public:
    // FIXME: コンストラクタでステート変更条件を渡せます
    StateMVOneOperationAnimation(std::vector<STATE_CHANGE_CRITERIA_DATA<int, STATE_ANEMATION_DATA>> stateChangeCriterias, int modelHandle, VECTOR changeVec = UtilCalc::VZero, VECTOR changeAngle = UtilCalc::VZero, VECTOR changeSize = UtilCalc::VZero);
    ~StateMVOneOperationAnimation() = default;

   /// <summary>この状態に入った時の処理</summary>
    /// <param name="animationData">アニメーション情報</param>
    /// <param name="preState">アニメーション種類</param>
    virtual void OnEnter(STATE_ANEMATION_DATA* animationData, ANIMATION_TYPE preState) override;
  /// <summary>この状態を出る時の処理</summary>
    /// <param name="animationData">アニメーション情報</param>
    /// <param name="nextState">次のアニメーション種類</param>
    virtual void OnExit(STATE_ANEMATION_DATA* animationData, ANIMATION_TYPE nextState) override;

    /// <summary>更新</summary>
    /// <param name="animation">アニメーション</param>
    /// <param name="animationDatas">アニメーション情報</param>
    virtual void Update(AnimationBase* animation, OneAnimationData *nowAnimationData) override;


protected:
    /*モデル種類が同類なら「true」を返す*/
    virtual bool CheckSimilarModelType(MODEL_TYPE modelType) override;
};


/*----------*/
/*【エフェクトアニメーション】
/*----------*/
class StateEffectAnimation : public IStateAnimation
{
private:
    int* mnEffectHandle;

public:
    // FIXME: コンストラクタでステート変更条件を渡せます
    StateEffectAnimation(int* effectHandle, std::vector<STATE_CHANGE_CRITERIA_DATA<int, STATE_ANEMATION_DATA>> stateChangeCriterias);
    ~StateEffectAnimation() = default;

   /// <summary>この状態に入った時の処理</summary>
    /// <param name="animationData">アニメーション情報</param>
    /// <param name="preState">アニメーション種類</param>
    virtual void OnEnter(STATE_ANEMATION_DATA* animationData, ANIMATION_TYPE preState) override;
  /// <summary>この状態を出る時の処理</summary>
    /// <param name="animationData">アニメーション情報</param>
    /// <param name="nextState">次のアニメーション種類</param>
    virtual void OnExit(STATE_ANEMATION_DATA* animationData, ANIMATION_TYPE nextState) override;

    /// <summary>終了</summary>
    virtual void Finalize(AnimationBase* animation, AnimationDatas* animationDatas) override;

    /// <summary>更新(何もしない)</summary>
    /// <param name="animation">アニメーション</param>
    /// <param name="animationDatas">アニメーション情報</param>
    virtual void Update(AnimationBase* animation, OneAnimationData *nowAnimationData) override;

private:
    /*モデル種類が同類なら「true」を返す*/
    bool CheckSimilarModelType(MODEL_TYPE modelType) override;

};


/*----------*/
/*【画像メーション】
/*----------*/
class StateGraphAnimation : public IStateAnimation
{
public:
    // FIXME: コンストラクタでステート変更条件を渡せます
    StateGraphAnimation(std::vector<STATE_CHANGE_CRITERIA_DATA<int, STATE_ANEMATION_DATA>> stateChangeCriterias);
    ~StateGraphAnimation() = default;

   /// <summary>この状態に入った時の処理</summary>
    /// <param name="animationData">アニメーション情報</param>
    /// <param name="preState">アニメーション種類</param>
    virtual void OnEnter(STATE_ANEMATION_DATA* animationData, ANIMATION_TYPE preState) override;
  /// <summary>この状態を出る時の処理</summary>
    /// <param name="animationData">アニメーション情報</param>
    /// <param name="nextState">次のアニメーション種類</param>
    virtual void OnExit(STATE_ANEMATION_DATA* animationData, ANIMATION_TYPE nextState) override;

    /// <summary>終了</summary>
    virtual void Finalize(AnimationBase* animation, AnimationDatas* animationDatas) override;

    /// <summary>更新(何もしない)</summary>
    /// <param name="animation">アニメーション</param>
    /// <param name="animationDatas">アニメーション情報</param>
    virtual void Update(AnimationBase* animation, OneAnimationData *nowAnimationData) override;

private:
    /*モデル種類が同類なら「true」を返す*/
    bool CheckSimilarModelType(MODEL_TYPE modelType) override;

};


/*----------*/
/*【動画アニメーション】
/*----------*/
class StateMovieAnimation : public IStateAnimation
{
public:
    // FIXME: コンストラクタでステート変更条件を渡せます
    StateMovieAnimation(std::vector<STATE_CHANGE_CRITERIA_DATA<int, STATE_ANEMATION_DATA>> stateChangeCriterias);
    ~StateMovieAnimation() = default;

   /// <summary>この状態に入った時の処理</summary>
    /// <param name="animationData">アニメーション情報</param>
    /// <param name="preState">アニメーション種類</param>
    virtual void OnEnter(STATE_ANEMATION_DATA* animationData, ANIMATION_TYPE preState) override;
  /// <summary>この状態を出る時の処理</summary>
    /// <param name="animationData">アニメーション情報</param>
    /// <param name="nextState">次のアニメーション種類</param>
    virtual void OnExit(STATE_ANEMATION_DATA* animationData, ANIMATION_TYPE nextState) override;

    /// <summary>終了</summary>
    virtual void Finalize(AnimationBase* animation, AnimationDatas* animationDatas) override;

    /// <summary>更新(何もしない)</summary>
    /// <param name="animation">アニメーション</param>
    /// <param name="animationDatas">アニメーション情報</param>
    virtual void Update(AnimationBase* animation, OneAnimationData *nowAnimationData) override;

private:
    /*モデル種類が同類なら「true」を返す*/
    bool CheckSimilarModelType(MODEL_TYPE modelType) override;

};

/*------------------------------*/
/*【フェード画像アニメーション】*/
/*------------------------------*/
class StateFadeGraphAnimation : public IStateAnimation
{
public:
    // FIXME: コンストラクタでステート変更条件を渡せます
    StateFadeGraphAnimation(std::vector<STATE_CHANGE_CRITERIA_DATA<int, STATE_ANEMATION_DATA>> stateChangeCriterias);
    ~StateFadeGraphAnimation() = default;

   /// <summary>この状態に入った時の処理</summary>
    /// <param name="animationData">アニメーション情報</param>
    /// <param name="preState">アニメーション種類</param>
    virtual void OnEnter(STATE_ANEMATION_DATA* animationData, ANIMATION_TYPE preState) override;
  /// <summary>この状態を出る時の処理</summary>
    /// <param name="animationData">アニメーション情報</param>
    /// <param name="nextState">次のアニメーション種類</param>
    virtual void OnExit(STATE_ANEMATION_DATA* animationData, ANIMATION_TYPE nextState) override;

    /// <summary>終了</summary>
    virtual void Finalize(AnimationBase* animation, AnimationDatas* animationDatas) override;
    /// <summary>更新(何もしない)</summary>
    /// <param name="animation">アニメーション</param>
    /// <param name="animationDatas">アニメーション情報</param>
    virtual void Update(AnimationBase* animation, OneAnimationData *nowAnimationData) override;

private:

    /*フェード処理*/
    void FadeProcess(OneAnimationData *nowAnimationData);

    /*モデル種類が同類なら「true」を返す*/
    bool CheckSimilarModelType(MODEL_TYPE modelType) override;
};

/*-------------------------*/
/*【DOTweenアニメーション】*/
/*-------------------------*/
class StateDOTweenAnimation : public IStateAnimation
{
public:
    // FIXME: コンストラクタでステート変更条件を渡せます
    StateDOTweenAnimation(std::vector<STATE_CHANGE_CRITERIA_DATA<int, STATE_ANEMATION_DATA>> stateChangeCriterias);
    ~StateDOTweenAnimation() = default;

   /// <summary>この状態に入った時の処理</summary>
    /// <param name="animationData">アニメーション情報</param>
    /// <param name="preState">アニメーション種類</param>
    virtual void OnEnter(STATE_ANEMATION_DATA* animationData, ANIMATION_TYPE preState) override;
  /// <summary>この状態を出る時の処理</summary>
    /// <param name="animationData">アニメーション情報</param>
    /// <param name="nextState">次のアニメーション種類</param>
    virtual void OnExit(STATE_ANEMATION_DATA* animationData, ANIMATION_TYPE nextState) override;
    
    /// <summary>終了</summary>
    virtual void Finalize(AnimationBase* animation, AnimationDatas* animationDatas) override;

    /// <summary>更新</summary>
    /// <param name="animation">アニメーション</param>
    /// <param name="animationDatas">アニメーション情報</param>
    virtual void Update(AnimationBase* animation, OneAnimationData *nowAnimationData) override;

private:
    /*モデル種類が同類なら「true」を返す*/
    bool CheckSimilarModelType(MODEL_TYPE modelType) override;
};