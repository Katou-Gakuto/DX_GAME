#pragma once
#include "StateData.h"

class FSMAnimation;
class ModelBase;

class Animation
{
private:
    // アニメーション有限状態マシン
    FSMAnimation* mpFsm;

    // アニメーションするモデル
    ModelBase* mpModel;

    // ステート情報(仮)
    STATE_ANEMATION_DATA mstStateData;

public:
    Animation();
    ~Animation() = default;

    /// <summary>初期化</summary>
    void Initilize(ModelBase* model);

    /// <summary>シーン最終初期化</summary>
    void SceneLastInitilize();

    /// <summary>終了</summary>
    void Finalize();

    /// <summary>アニメーション更新</summary>
    void Update();

    /*----------*/
    /*【設定・取得】
    /*----------*/
    /// <summary>アニメーション有限状態マシン取得</summary>
    inline FSMAnimation* GetFsm() const { return mpFsm; }
    /// <summary>アニメーション有限状態マシン設定</summary>
    inline void SetFsm(FSMAnimation* fsm) { mpFsm = fsm; }

    /// <summary>モデル取得</summary>
    inline ModelBase* GetModel() { return mpModel; }
};
// #include <map>
// #include <vector>

// #include "ModelsControllerBase.h"

// #include "FSMAnimation.h"

// class AnimationBase
// {
// private:
//     // モデルコントローラー
//     ModelsControllerBase* mpModelsController;

//     // アニメーション有限状態マシン
//     FSMAnimation* mpFsm;    

//     // アニメーションデータ
//     std::vector<AnimationDatas*> mstAnimationDatas;

//     // アニメーション時間
//     std::map<ANIMATION_TYPE, int> mmAnimationTime;

// public:
//     AnimationBase();
//     ~AnimationBase() = default;

//     /// <summary>初期化</summary>
//     void Initilize();

//     /// <summary>シーン最終初期化</summary>
//     void SceneLastInitilize();

//     /// <summary>終了</summary>
//     void Finalize();

//     /// <summary>アニメーション更新</summary>
//     void Update();

//     /// <summary>アニメーションデータ追加</summary>
//     inline void AddAnimationData(AnimationDatas* animationData) { mstAnimationDatas.push_back(animationData); }

//     /// <summary>アニメション種類探索</summary>
//     inline bool SearchAnimationType(ANIMATION_TYPE animationType) { return (mmAnimationTime.find(animationType) != mmAnimationTime.end()); }

//     /*----------*/
//     /*【設定・取得】
//     /*----------*/
// public:
//     /// <summary>モデルコントローラー取得</summary>
//     inline ModelsControllerBase* GetModelsController() const { return mpModelsController; }
//     /// <summary>モデルコントローラー設定</summary>
//     inline void SetModelsController(ModelsControllerBase* modelsController) { mpModelsController = modelsController; }

//     /// <summary>アニメーション有限状態マシン取得</summary>
//     inline FSMAnimation* GetFsm() const { return mpFsm; }
//     /// <summary>アニメーション有限状態マシン設定</summary>
//     inline void SetFsm(FSMAnimation* fsm) { mpFsm = fsm; }

//     /// <summary>アニメーションデータ取得</summary>
//     inline std::vector<AnimationDatas*>& GetAnimationDatas() { return mstAnimationDatas; }
//     /// <summary>アニメーションデータ設定</summary>
//     inline void SetAnimationDatas(const std::vector<AnimationDatas*>& animationDatas) { mstAnimationDatas = animationDatas; }

//     // /// <summary>アニメーション種類取得</summary>
//     // inline ANIMATION_TYPE GetAnimationType() { if(mpFsm!=nullptr){return mpFsm->GetCurrentState();} return ANIMATION_TYPE::NONE; }
//     // /// <summary>アニメーション種類設定</summary>
//     // inline void SetAnimationType(ANIMATION_TYPE animationType) { if(mpFsm!=nullptr){mpFsm->SetNextState(animationType);} }

//     // /// <summary>アニメーション時間取得</summary>
//     // inline int GetAnimationTime(ANIMATION_TYPE animationType) { return mmAnimationTime[animationType]; }
//     // /// <summary>アニメーション時間設定</summary>
//     // inline void SetAnimationTime(ANIMATION_TYPE animationType, int time) { mmAnimationTime[animationType] = time; }
//     // /// <summary>全アニメーション時間設定</summary>
//     // inline void SetAllAnimationTime(std::map<ANIMATION_TYPE, int> animationTime) { mmAnimationTime = animationTime; }
// };